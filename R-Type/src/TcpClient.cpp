/*
** EPITECH PROJECT, 2023
** TcpClient.cpp
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

RType::Client::TcpClient::TcpClient(asio::io_context &IOContext, asio::ip::tcp::endpoint &serverEndpoint)
    : _IOContext(IOContext), _serverEndpoint(serverEndpoint), _socket(IOContext, _serverEndpoint)
{
    _tcpRunning = false;
}

RType::Client::TcpClient::~TcpClient() { _socket.close(); }

bool &RType::Client::TcpClient::getTcpStatus()
{
    return _tcpRunning;
}

void RType::Client::TcpClient::handleInput(const asio::error_code &error, std::size_t recvBytes)
{
    if (!error) {
        asio::streambuf::const_buffers_type bufs = _inputBuffer.data();
        std::string str(asio::buffers_begin(bufs), asio::buffers_begin(bufs) + recvBytes);
        asio::async_write(
            _socket, asio::buffer(str), std::bind(&RType::Client::TcpClient::handleWrite, this, std::placeholders::_1));
        _inputBuffer.consume(_inputBuffer.size());
    } else if (error == asio::error::operation_aborted) {
        _socket.close();
    }
}



void RType::Client::TcpClient::handleWrite(const asio::error_code &error)
{
    _tcpRunning = true;
    if (!error) {
        std::cout << "Enter" << std::endl;
        // asio::async_read_until(_input, _inputBuffer, '\n',
            // std::bind(&RType::Client::TcpClient::handleInput, this, std::placeholders::_1, std::placeholders::_2));
    } else if (error == asio::error::operation_aborted) {
        std::cout << "WOWOWOOWOWO" << std::endl;
        // _socket.close();
    } else {
        _socket.close();
    }
}

void RType::Client::TcpClient::run()
{
    std::cout << "Connect to TCP" << std::endl;
    _socket.async_connect(
        _serverEndpoint, std::bind(&RType::Client::TcpClient::handleWrite, this, std::placeholders::_1));
}
