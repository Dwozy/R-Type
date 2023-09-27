/*
** EPITECH PROJECT, 2023
** Client.cpp
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(boost::asio::io_context &IOContext,
    boost::asio::ip::udp::endpoint &serverUdpEndpoint,
    boost::asio::ip::tcp::endpoint &serverTcpEndpoint):
    _serverTcpSocket(IOContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::udp::v4(), 0)),
    _serverUdpSocket(IOContext, boost::asio::ip::udp::endpoint(boost::asio::ip::tcp::v4(), 0)),
    _serverTcpEndpoint(serverTcpEndpoint),
    _serverUdpEndpoint(serverUdpEndpoint)
{
}

Client::~Client()
{
}
