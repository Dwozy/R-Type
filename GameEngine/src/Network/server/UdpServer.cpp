/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "Network/Server/UdpServer.hpp"

namespace GameEngine::Network
{
    UdpServer::UdpServer(asio::io_context &IOContext, int port, SafeQueue<std::string> &clientsMessages)
        : _socket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _IOContext(IOContext),
          _timer(IOContext), _timerTCP(IOContext), _clientsMessages(clientsMessages), _buffer(_streamBuffer.prepare(1))
    {
        receive();
        updateGameInfo();
        updateTCPInformation();
    }

    UdpServer::~UdpServer()
    {
        std::string message = "Server down";
        for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
            _communication.sendData(message.data(), message.size(), static_cast<uint8_t>(rtype::PacketType::STRING),
                _socket, client.second);
        }
        _socket.close();
    }

    void UdpServer::handleReceive(const asio::error_code &error, std::size_t)
    {
        if (!error) {
            if (_listClient.find(_clientEndpoint.port()) == _listClient.end()) {
                _listClient[_clientEndpoint.port()] = std::move(_clientEndpoint);
            }
            receive();
        }
    }

    void UdpServer::receive()
    {
        _buffer = _streamBuffer.prepare(1);

        _socket.async_receive_from(asio::buffer(_buffer), _clientEndpoint,
            [&](const asio::error_code &error, std::size_t bytes_received) { handleReceive(error, bytes_received); });
    }

    void UdpServer::updateTCPInformation()
    {
        std::string buff;

        while (_clientsMessages.tryPop(buff)) {
            for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
                if (buff == "Room\n") {
                    std::cout << "BUFF : " << buff;
                    struct rtype::Room room;
                    room.id = 1;
                    room.slots = 4;
                    room.slotsLeft = 4;
                    room.stageLevel = 1;
                    std::vector<std::byte> byteArrayToSend;
                    byteArrayToSend.resize(sizeof(room));
                    std::memcpy(byteArrayToSend.data(), &room, sizeof(room));
                    _communication.sendData(byteArrayToSend.data(), byteArrayToSend.size(),
                        static_cast<uint8_t>(rtype::PacketType::ROOM), _socket, client.second);
                } else
                    _communication.sendData(buff.data(), buff.size(), static_cast<uint8_t>(rtype::PacketType::STRING),
                        _socket, client.second);
            }
        }
        _timerTCP.expires_from_now(std::chrono::seconds(0));
        _timerTCP.async_wait(std::bind(&UdpServer::updateTCPInformation, this));
    }

    void UdpServer::sender()
    {
        for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
            std::string message = "Sender endpoint : ";
            message += client.second.address().to_string().c_str();
            message += " on port : ";
            message += client.second.address().to_string();
            message += " ";
            message += std::to_string((int)client.second.port());
            message += " with message : \n";

            message.erase(std::remove(message.begin(), message.end(), '\0'), message.end());
            _communication.sendData(message.data(), message.size(), static_cast<uint8_t>(rtype::PacketType::STRING),
                _socket, client.second);
        }
        updateGameInfo();
    }

    void UdpServer::updateGameInfo()
    {
        _timer.expires_from_now(std::chrono::milliseconds(2000));
        _timer.async_wait(std::bind(&UdpServer::sender, this));
    }
} // namespace GameEngine::Network
