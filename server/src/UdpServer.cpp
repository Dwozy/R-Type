/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

Network::UdpServer::UdpServer(boost::asio::io_context &IOContext, int port) :
    _socket(IOContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
    _IOContext(IOContext)
{
    receive();
}

Network::UdpServer::~UdpServer()
{
    std::string message = "END OF SERVER\n";
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
        sender(std::string(_readBuffer.begin(), _readBuffer.begin() + recvBytes));
    }
}

void Network::UdpServer::receive()
{
    _socket.async_receive_from(boost::asio::buffer(_readBuffer, 1024), _clientEndpoint,
        [&] (const boost::system::error_code &error, std::size_t bytes_received) {
            handleReceive(error, bytes_received);
        });
}

void Network::UdpServer::sender(std::string buffer)
{
    std::string message = "Sender endpoint : ";
    message += _clientEndpoint.address().to_string().c_str();
    message += " on port : ";
    message += _clientEndpoint.address().to_string();
    message += " ";
    message += std::to_string((int) _clientEndpoint.port());
    message +=  " with message : ";
    message += buffer;
    if (_listClient.find(_clientEndpoint.port()) == _listClient.end())
        _listClient[_clientEndpoint.port()] = std::move(_clientEndpoint);
    _socket.async_send_to(boost::asio::buffer(message.c_str(), message.length()), _clientEndpoint,
        boost::bind(&UdpServer::receive, this));
}
