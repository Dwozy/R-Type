/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

Network::UdpServer::UdpServer(asio::io_context &IOContext, int port,
                              SafeQueue<std::string> &clientsMessages)
    : _socket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
      _IOContext(IOContext), _timer(IOContext), _timerTCP(IOContext),
      _clientsMessages(clientsMessages)
{
    receive();
    updateGameInfo();
    updateTCPInformation();
}

Network::UdpServer::~UdpServer()
{
    std::string message = "Server down";
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client :
         _listClient) {
            uint16_t size = getArchiveDataSize<std::string>(message);
            sendHeader(size, client.second);
            sendArchiveData<std::string>(message, client.second);
    }
    _socket.close();
}

void Network::UdpServer::handleReceive(const asio::error_code &error,
                                       std::size_t)
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

    _socket.async_receive_from(
        asio::buffer(_readBuffer, 1), _clientEndpoint,
        [&](const asio::error_code &error, std::size_t bytes_received) {
            handleReceive(error, bytes_received);
        });
}

void Network::UdpServer::updateTCPInformation()
{
    asio::streambuf streamBuffer;
    std::ostream os(&streamBuffer);
    std::string buff;

    while (_clientsMessages.tryPop(buff)) {
        for (std::pair<unsigned short, asio::ip::udp::endpoint> client :
             _listClient) {

            uint16_t size = getArchiveDataSize<std::string>(buff);
            sendHeader(size, client.second);
            sendArchiveData<std::string>(buff, client.second);
        }
    }
    _timerTCP.expires_from_now(std::chrono::seconds(0));
    _timerTCP.async_wait(
        std::bind(&Network::UdpServer::updateTCPInformation, this));
}

void Network::UdpServer::sendHeader(
    std::size_t size, const asio::ip::udp::endpoint &clientEndpoint)
{
    struct rtype::HeaderDataPacket header;

    header.payloadSize = size;
    sendArchiveData<struct rtype::HeaderDataPacket>(header, clientEndpoint);
}

void Network::UdpServer::sender()
{
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client :
         _listClient) {
        std::string message = "Sender endpoint : ";
        message += client.second.address().to_string().c_str();
        message += " on port : ";
        message += client.second.address().to_string();
        message += " ";
        message += std::to_string((int)client.second.port());
        message += " with message : \n";

        uint16_t size = getArchiveDataSize<std::string>(message);
        sendHeader(size, client.second);
        sendArchiveData<std::string>(message, client.second);
    }
    updateGameInfo();
}

void Network::UdpServer::updateGameInfo()
{
    _timer.expires_from_now(std::chrono::milliseconds(2000));
    _timer.async_wait(std::bind(&Network::UdpServer::sender, this));
}
