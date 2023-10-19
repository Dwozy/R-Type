/*
** EPITECH PROJECT, 2023
** ACommunication.cpp
** File description:
** ACommunication
*/

#include "Network/ACommunication.hpp"

GameEngine::Network::ACommunication::ACommunication(asio::io_context &IOContext, unsigned short port)
    : _socket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _buffer(_streamBuffer.prepare(0))
{
}

void GameEngine::Network::ACommunication::sendInformation(void *data, std::size_t size, asio::ip::udp::socket &socket,
    asio::ip::udp::endpoint &endpoint, struct rtype::HeaderDataPacket &header)
{
    socket.async_send_to(asio::buffer(&header, sizeof(rtype::HeaderDataPacket)), endpoint,
        [&](const asio::error_code &, std::size_t) {});
    socket.async_send_to(asio::buffer(data, size), endpoint, [&](const asio::error_code &, std::size_t) {});
}

void GameEngine::Network::ACommunication::sendInformation(void *data, std::size_t size, asio::ip::tcp::socket &socket,
    asio::ip::tcp::endpoint &, struct rtype::HeaderDataPacket &header)
{
    asio::async_write(socket, asio::buffer(&header, sizeof(header)), [&](const asio::error_code &, std::size_t) {});
    asio::async_write(socket, asio::buffer(data, size), [&](const asio::error_code &, std::size_t) {});
}

void GameEngine::Network::ACommunication::handleReceive(
    const asio::error_code &error, std::size_t recvBytes, struct rtype::HeaderDataPacket &header)
{
    if (!error) {
        if (_listClient.find(_endpoint.port()) == _listClient.end()) {
            _listClient[_endpoint.port()] = std::move(_endpoint);
        }
        _streamBuffer.commit(recvBytes);
        std::memcpy(&header, _buffer.data(), recvBytes);
        if (header.magicNumber != rtype::MAGIC_NUMBER) {
            std::cout << "When PacketType is broke : " << static_cast<std::size_t> (header.packetType) << std::endl;
            std::cout << "When Body is broke : " << static_cast<std::size_t> (header.payloadSize) << std::endl;
            std::cerr << "Invalid Magic Number Packet" << std::endl;
            // return;
        }
        _streamBuffer.consume(recvBytes);
        _buffer = _streamBuffer.prepare(header.payloadSize);
        _socket.async_receive_from(_buffer, _endpoint,
            std::bind(&GameEngine::Network::ACommunication::handleData, this, std::placeholders::_1,
                std::placeholders::_2, header));
    } else {
        std::cerr << "Error : " << error.message() << std::endl;
    }
}

void GameEngine::Network::ACommunication::readHeader()
{
    _buffer = _streamBuffer.prepare(rtype::HEADER_SIZE);
    _socket.async_receive_from(_buffer, _endpoint,
        std::bind(&GameEngine::Network::ACommunication::handleReceive, this, std::placeholders::_1,
            std::placeholders::_2, _header));
}
