/*
** EPITECH PROJECT, 2023
** UdpClient.cpp
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

Network::UdpClient::UdpClient(asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint)
    : _socket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)), _serverEndpoint(serverEndpoint),
      _IOContext(IOContext), _buffer(_streamBuffer.prepare(rtype::HEADER_SIZE))
{
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ROOM), getRoom);
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::STRING), getString);
    run();
}

void Network::getRoom(Network::UdpClient &client, uint16_t size)
{
    struct rtype::Room room = Serialization::deserializeData<struct rtype::Room>(client._buffer, size);

    std::cout << "----------" << std::endl;
    std::cout << "Room : " << std::endl;
    std::cout << "Id : " << room.id << " with " << static_cast<std::size_t>(room.slotsUsed) << "/"
              << static_cast<std::size_t>(room.slots) << " lefts." << std::endl;
    std::cout << "Stage level : " << room.stageLevel << std::endl;
    std::cout << "----------" << std::endl;
    client._streamBuffer.consume(client._streamBuffer.size());
    // std::cout << client._message << std::endl;
}

void Network::getString(Network::UdpClient &client, uint16_t size)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(client._buffer, size);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
    client._message = message;
    std::cout << "Message : " << client._message << std::endl;
}

Network::UdpClient::~UdpClient() { _socket.close(); }

void Network::UdpClient::handleTimeout()
{
    asio::steady_timer timeout(_IOContext);
    timeout.expires_from_now(std::chrono::seconds(5));
    timeout.async_wait([&](const asio::error_code &error) {
        if (!error) {
            _socket.cancel();
            std::cerr << "Timeout on response from server !" << std::endl;
        }
    });
    readHeader();
}

void Network::UdpClient::handleData(
    const asio::error_code &error, std::size_t, const struct rtype::HeaderDataPacket &header)
{
    if (!error) {
        if (_commands.find(header.packetType) != _commands.end()) {
            std::cout << header.payloadSize << std::endl;
            _commands.at(header.packetType)(*this, header.payloadSize);
        } else {
            std::cerr << "Packet Type doesn't exist !" << std::endl;
        }
        _streamBuffer.consume(header.payloadSize);
        handleTimeout();
    }
}

void Network::UdpClient::handleReceive(const asio::error_code &error, std::size_t recvBytes)
{
    if (!error) {
        _streamBuffer.commit(recvBytes);
        std::memcpy(&_header, _buffer.data(), recvBytes);
        if (_header.magicNumber != rtype::MAGIC_NUMBER) {
            std::cerr << "Invalid Magic Number Packet" << std::endl;
            _streamBuffer.consume(recvBytes);
            handleTimeout();
        }
        _streamBuffer.consume(recvBytes);
        _buffer = _streamBuffer.prepare(_header.payloadSize);
        _socket.async_receive_from(_buffer, _serverEndpoint,
            std::bind(&Network::UdpClient::handleData, this, std::placeholders::_1, std::placeholders::_2, _header));
    } else {
        std::cerr << "Error : " << error.message() << std::endl;
    }
}

void Network::UdpClient::readHeader()
{
    _buffer = _streamBuffer.prepare(rtype::HEADER_SIZE);
    _socket.async_receive_from(_buffer, _serverEndpoint,
        std::bind(&Network::UdpClient::handleReceive, this, std::placeholders::_1, std::placeholders::_2));
}

void Network::UdpClient::run()
{
    std::string buff;
    std::array<char, 1> data;
    std::copy(buff.begin(), buff.end(), data.begin());
    _socket.async_send_to(
        asio::buffer(data, buff.size()), _serverEndpoint, std::bind(&Network::UdpClient::readHeader, this));
}
