/*
** EPITECH PROJECT, 2023
** ACommunication.cpp
** File description:
** ACommunication
*/

#include "Network/ACommunication.hpp"
#include "Network/Serialization.hpp"
#include <iterator>

GameEngine::Network::ACommunication::ACommunication(asio::io_context &IOContext, unsigned short port)
    : _udpSocket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _buffer(_streamBuffer.prepare(0))
{
}

void GameEngine::Network::ACommunication::sendInformation(void *data, std::size_t size, asio::ip::udp::socket &socket,
    asio::ip::udp::endpoint &endpoint, struct rtype::HeaderDataPacket &header)
{
    std::vector<std::byte> byteArray =
        Serialization::serializeData<struct rtype::HeaderDataPacket>(header, sizeof(header));
    std::vector<std::byte> byteArrayBody(static_cast<std::byte *>(data), static_cast<std::byte *>(data) + size);

    byteArray.insert(
        byteArray.end(), std::make_move_iterator(byteArrayBody.begin()), std::make_move_iterator(byteArrayBody.end()));
    socket.async_send_to(
        asio::buffer(byteArray.data(), byteArray.size()), endpoint, [&](const asio::error_code &, std::size_t) {});
}

void GameEngine::Network::ACommunication::sendInformation(void *data, std::size_t size, asio::ip::tcp::socket &socket,
    asio::ip::tcp::endpoint &, struct rtype::HeaderDataPacket &header)
{
    std::vector<std::byte> byteArray =
        Serialization::serializeData<struct rtype::HeaderDataPacket>(header, sizeof(header));
    std::vector<std::byte> byteArrayBody(static_cast<std::byte *>(data), static_cast<std::byte *>(data) + size);

    byteArray.insert(
        byteArray.end(), std::make_move_iterator(byteArrayBody.begin()), std::make_move_iterator(byteArrayBody.end()));
    asio::async_write(
        socket, asio::buffer(byteArray.data(), byteArray.size()), [&](const asio::error_code &, std::size_t) {});
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
        _streamBuffer.consume(sizeof(header));
        if (header.magicNumber != rtype::MAGIC_NUMBER)
            std::cerr << "Invalid Magic Number" << std::endl;
        else
            handleData(header);
        _streamBuffer.consume(rtype::MAX_BUFFER_SIZE - sizeof(header));
        readHeader();
    } else {
        std::cerr << "Error : " << error.message() << std::endl;
    }
}

void GameEngine::Network::ACommunication::readHeader()
{
    _buffer = _streamBuffer.prepare(rtype::MAX_BUFFER_SIZE);
    _udpSocket.async_receive_from(_buffer, _endpoint,
        std::bind(&GameEngine::Network::ACommunication::handleReceive, this, std::placeholders::_1,
            std::placeholders::_2, _header));
}
