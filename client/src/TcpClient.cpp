/*
** EPITECH PROJECT, 2023
** TcpClient.cpp
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

Network::TcpClient::TcpClient(asio::io_context &IOContext,
                              asio::ip::tcp::endpoint &serverEndpoint)
    : _IOContext(IOContext), _serverEndpoint(serverEndpoint),
      _socket(IOContext), _input(IOContext, ::dup(STDIN_FILENO))
{
    run();
}

Network::TcpClient::~TcpClient() { _input.close(); }

void Network::TcpClient::handleInput(const asio::error_code &error,
                                     std::size_t recvBytes)
{
    if (!error) {
        asio::streambuf::const_buffers_type bufs = _inputBuffer.data();
        std::string str(asio::buffers_begin(bufs),
                        asio::buffers_begin(bufs) + recvBytes);
        asio::async_write(_socket, asio::buffer(str),
                          std::bind(&Network::TcpClient::handleWrite, this,
                                    std::placeholders::_1));
        _inputBuffer.consume(_inputBuffer.size());
    } else if (error == asio::error::operation_aborted) {
        _socket.close();
        _input.close();
    }
}

void Network::TcpClient::handleWrite(const asio::error_code &error)
{
    if (!error) {
        asio::async_read_until(_input, _inputBuffer, '\n',
                               std::bind(&Network::TcpClient::handleInput, this,
                                         std::placeholders::_1,
                                         std::placeholders::_2));
    } else if (error == asio::error::operation_aborted) {
        std::cout << "Server DOWN" << std::endl;
        _socket.close();
        _input.close();
    } else {
        _socket.close();
    }
}

void Network::TcpClient::run()
{
    _socket.async_connect(_serverEndpoint,
                          std::bind(&Network::TcpClient::handleWrite, this,
                                    std::placeholders::_1));
}
