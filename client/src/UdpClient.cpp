/*
** EPITECH PROJECT, 2023
** Udpcpp
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

RType::Client::UdpClient::UdpClient(asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint)
    : ACommunication(IOContext, 0), _IOContext(IOContext), _serverEndpoint(serverEndpoint)
{
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ROOM),
        std::bind(&RType::Client::UdpClient::handleRoom, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::STRING),
        std::bind(&RType::Client::UdpClient::handleString, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ENTITY),
        std::bind(&RType::Client::UdpClient::handleEntity, this, std::placeholders::_1));
    run();
    readHeader();
}

RType::Client::UdpClient::~UdpClient() { _socket.close(); }

void RType::Client::UdpClient::handleRoom(uint16_t size)
{
    struct rtype::Room room = Serialization::deserializeData<struct rtype::Room>(_buffer, size);

    std::cout << "----------" << std::endl;
    std::cout << "Room : " << std::endl;
    std::cout << "Id : " << room.id << " with " << static_cast<std::size_t>(room.slotsUsed) << "/"
              << static_cast<std::size_t>(room.slots) << " lefts." << std::endl;
    std::cout << "Stage level : " << room.stageLevel << std::endl;
    std::cout << "----------" << std::endl;
    _streamBuffer.consume(_streamBuffer.size());
    // std::cout << _message << std::endl;
}

void RType::Client::UdpClient::handleString(uint16_t size)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(_buffer, size);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
    // _message = message;
    std::cout << "Message : " << message << std::endl;
    if (message == "Server down")
        _IOContext.stop();
}

void RType::Client::UdpClient::handleEntity(uint16_t size)
{
    struct rtype::Entity entity = Serialization::deserializeData<struct rtype::Entity>(_buffer, size);

    _listPlayersInfos[entity.id] = entity;
    // if (_listPlayersInfos.find(entity.id) != _listPlayersInfos.end()) {
    // _listPlayersInfos. = entity;
    // } else
    // _list
    std::cout << "----------------" << std::endl;
    std::cout << "Entity number : " << entity.id << std::endl;
    std::cout << "Pos : " << entity.positionX << " - " << entity.positionY << std::endl;
    std::cout << "Direction : " << entity.directionX << " - " << entity.directionY << std::endl;
    std::cout << "LifePoint : " << entity.lifePoint << std::endl;
    std::cout << "----------------" << std::endl;
}

void RType::Client::UdpClient::handleData(
    const asio::error_code &error, std::size_t, const struct rtype::HeaderDataPacket &header)
{
    if (!error) {
        if (_commands.find(header.packetType) != _commands.end()) {
            std::cout << header.payloadSize << std::endl;
            _commands.at(header.packetType)(header.payloadSize);
        } else {
            std::cerr << "Packet Type doesn't exist !" << std::endl;
        }
        _streamBuffer.consume(header.payloadSize);
        readHeader();
    }
}

void RType::Client::UdpClient::run()
{
    // std::string message = "Player 1";
    // message.erase(std::remove(message.begin(), message.end(), '\0'), message.end());
    sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(
        0, 0, static_cast<uint8_t>(rtype::PacketType::CONNEXION), _socket, _serverEndpoint);
    // std::string buff;
    // std::array<char, 1> data;
    // std::copy(buff.begin(), buff.end(), data.begin());
    // _socket.async_send_to(
    //     asio::buffer(data, buff.size()), _serverEndpoint, std::bind(&RType::Client::UdpClient::readHeader, this));
}
