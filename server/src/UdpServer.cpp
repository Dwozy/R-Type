/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

UdpServer::UdpServer(asio::io_context &IOContext, int port) :
    _socket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    asio::signal_set signal(IOContext);
    signal.add(SIGINT);
    signal.add(SIGTERM);
    signal.async_wait([&] (const asio::error_code &, int) { IOContext.stop(); });
    receive();
    IOContext.run();
}

UdpServer::~UdpServer()
{
    _socket.close();
}

void UdpServer::stop()
{

}

void UdpServer::handleReceive(const asio::error_code &error, std::size_t recvBytes)
{
    if (!error) {
        std::cout << "Received " << recvBytes << " bytes of data" << std::endl;
        std::cout << "data: " << std::string(_readBuffer.begin(), _readBuffer.begin() + recvBytes);
        sender(std::string(_readBuffer.begin(), _readBuffer.begin() + recvBytes));
    }
}

void UdpServer::receive()
{
    _socket.async_receive_from(asio::buffer(_readBuffer, 1024), _clientEndpoint,
        [&] (const asio::error_code& error, std::size_t bytes_received) {
            handleReceive(error, bytes_received);
        });
}

void UdpServer::sender(std::string buffer)
{
    std::string message = "Sender endpoint : ";
    message += _clientEndpoint.address().to_string().c_str();
    message += " on port : ";
    message += std::to_string((int) _clientEndpoint.port());
    message +=  " with message : ";
    message += buffer;
    _socket.async_send_to(asio::buffer(message.c_str(), message.length()), _clientEndpoint,
        [&] (const std::error_code &, std::size_t) {
            receive();
        });
}
