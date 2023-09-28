/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

Network::UdpServer::UdpServer(boost::asio::io_context &IOContext, int port, SafeQueue<std::string> &clientsMessages) :
    _socket(IOContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
    _IOContext(IOContext),
    _timer(IOContext),
    _timerTCP(IOContext),
    _clientsMessages(clientsMessages)
{
    receive();
    updateGameInfo();
    updateTCPInformation();
}

Network::UdpServer::~UdpServer()
{
    std::string message = "Server down";
    for (std::pair<unsigned short, boost::asio::ip::udp::endpoint> elem : _listClient) {
        _socket.send_to(boost::asio::buffer(message.c_str(), message.length()), elem.second);
    }
    _socket.close();
}

void Network::UdpServer::handleReceive(const boost::system::error_code &error, std::size_t recvBytes)
{
    if (!error) {
        std::cout << "Received " << recvBytes << " bytes of data" << std::endl;
        std::cout << "data: " << std::string(_readBuffer.begin(), _readBuffer.begin() + recvBytes);
        if (_listClient.find(_clientEndpoint.port()) == _listClient.end())
            _listClient[_clientEndpoint.port()] = std::move(_clientEndpoint);
        receive();
    }
}

void Network::UdpServer::receive()
{

    _socket.async_receive_from(boost::asio::buffer(_readBuffer, 1024), _clientEndpoint,
        [&] (const boost::system::error_code &error, std::size_t bytes_received) {
            handleReceive(error, bytes_received);
        });
}

void Network::UdpServer::updateTCPInformation()
{
    std::string buff;

    while (_clientsMessages.tryPop(buff)) {
        for (std::pair<unsigned short, boost::asio::ip::udp::endpoint> client : _listClient)
            _socket.send_to(boost::asio::buffer(buff.c_str(), buff.length()), client.second);
    }
    _timerTCP.expires_from_now(boost::posix_time::seconds(0));
    _timerTCP.async_wait(boost::bind(&Network::UdpServer::updateTCPInformation, this));
}

void Network::UdpServer::updateGameInfo()
{
    _timer.expires_from_now(boost::posix_time::seconds(2));
    _timer.async_wait(boost::bind(&Network::UdpServer::sender, this));
}

void Network::UdpServer::sender()
{
    for (std::pair<unsigned short, boost::asio::ip::udp::endpoint> client : _listClient) {
        std::string message = "Sender endpoint : ";
        message += client.second.address().to_string().c_str();
        message += " on port : ";
        message += client.second.address().to_string();
        message += " ";
        message += std::to_string((int) client.second.port());
        message +=  " with message : \n";
        _socket.send_to(boost::asio::buffer(message.c_str(), message.length()), client.second);
    }
    updateGameInfo();
}
