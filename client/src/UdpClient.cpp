/*
** EPITECH PROJECT, 2023
** UdpClient.cpp
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_context &IOContext, boost::asio::ip::udp::endpoint &serverEndpoint)
    : _socket(IOContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
      _serverEndpoint(serverEndpoint),
      _IOContext(IOContext)
{
    run();
}

UdpClient::~UdpClient()
{
    _socket.close();
}

void UdpClient::handleReceive(const boost::system::error_code &error, std::size_t recvBytes)
{
    if (!error) {
        std::cout << std::string(_readBuffer.begin(), _readBuffer.begin() + recvBytes);
        receive();
    }
}

void UdpClient::receive()
{
    _socket.async_receive_from(boost::asio::buffer(_readBuffer, 1024), _serverEndpoint,
        boost::bind(&UdpClient::handleReceive, this, boost::placeholders::_1, boost::placeholders::_2));
}

void UdpClient::run()
{
    std::string buff;
    std::array<char, 1> data;
    std::copy(buff.begin(), buff.end(), data.begin());
    _socket.async_send_to(boost::asio::buffer(data, buff.size()), _serverEndpoint,
        boost::bind(&UdpClient::receive, this));
}
