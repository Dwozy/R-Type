/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

Network::UdpServer::UdpServer(asio::io_context &IOContext, int port, SafeQueue<std::string> &clientsMessages)
    : _socket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _IOContext(IOContext), _timer(IOContext),
      _timerTCP(IOContext), _clientsMessages(clientsMessages), _buffer(_streamBuffer.prepare(1))
{
    index = 0;
    receive();
    updateGameInfo();
    updateTCPInformation();
}

Network::UdpServer::~UdpServer()
{
    std::string message = "Server down";
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
        _communication.sendData(
            message.data(), message.size(), static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
    }
    _socket.close();
}

void Network::UdpServer::handleReceive(const asio::error_code &error, std::size_t)
{
    if (!error) {
        if (_listClient.find(_clientEndpoint.port()) == _listClient.end()) {
            _listClient[_clientEndpoint.port()] = std::move(_clientEndpoint);
        }
        receive();
    }
}

void Network::UdpServer::receive()
{
    _buffer = _streamBuffer.prepare(rtype::HEADER_SIZE);

    _socket.async_receive_from(_buffer, _clientEndpoint,
        [&](const asio::error_code &error, std::size_t bytes_received) { handleReceive(error, bytes_received); });
}

void Network::UdpServer::updateTCPInformation()
{
    std::string buff;

    while (_clientsMessages.tryPop(buff)) {
        for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
            if (buff == "Create Room\n") {
                std::cout << "BUFF : " << buff;
                struct rtype::Room room;
                room.id = index;
                room.slots = 4;
                room.slotsUsed = 4;
                room.stageLevel = 1;
                _listRooms.insert({index, {"Room " + std::to_string(static_cast<std::size_t>(index)), room}});
                std::cout << "Room " + std::to_string(static_cast<std::size_t>(index)) << std::endl;
                _communication.sendData(Serialization::serializeData<struct rtype::Room>(room).data(),
                    Serialization::serializeData<struct rtype::Room>(room).size(),
                    static_cast<uint8_t>(rtype::PacketType::ROOM), _socket, client.second);
                _communication.sendData(_listRooms.at(index).first.data(), _listRooms.at(index).first.size(),
                    static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
            } else
                _communication.sendData(
                    buff.data(), buff.size(), static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
        }
    }
    _timerTCP.expires_from_now(std::chrono::seconds(0));
    _timerTCP.async_wait(std::bind(&Network::UdpServer::updateTCPInformation, this));
}

void Network::UdpServer::sender()
{
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
        std::string message = "Sender endpoint : ";
        message += client.second.address().to_string().c_str();
        message += " on port : ";
        message += client.second.address().to_string();
        message += " ";
        message += std::to_string(static_cast<int>(client.second.port()));
        message += " with message : \n";

        message.erase(std::remove(message.begin(), message.end(), '\0'), message.end());
        _communication.sendData(
            message.data(), message.size(), static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
    }
    updateGameInfo();
}

void Network::UdpServer::updateGameInfo()
{
    _timer.expires_from_now(std::chrono::milliseconds(2000));
    _timer.async_wait(std::bind(&Network::UdpServer::sender, this));
}
