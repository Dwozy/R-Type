/*
** EPITECH PROJECT, 2023
** TcpClient.cpp
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

TcpClient::TcpClient(boost::asio::io_context &IOContext,
                     boost::asio::ip::tcp::endpoint &serverEndpoint)
    : _IOContext(IOContext), _serverEndpoint(serverEndpoint),
      _socket(IOContext), _input(IOContext, ::dup(STDIN_FILENO))
{
    run();
}

TcpClient::~TcpClient() { _input.close(); }

void TcpClient::handleInput(const boost::system::error_code &error,
                            std::size_t recvBytes)
{
    if (!error) {
        boost::asio::streambuf::const_buffers_type bufs = _inputBuffer.data();
        std::string str(boost::asio::buffers_begin(bufs),
                        boost::asio::buffers_begin(bufs) + recvBytes);
        boost::asio::async_write(_socket, boost::asio::buffer(str),
                                 boost::bind(&TcpClient::handleWrite, this,
                                             boost::placeholders::_1));
        _inputBuffer.consume(_inputBuffer.size());
    } else if (error == boost::asio::error::operation_aborted) {
        _socket.close();
        _input.close();
    }
}

void TcpClient::handleWrite(const boost::system::error_code &error)
{
    if (!error) {
        boost::asio::async_read_until(_input, _inputBuffer, '\n',
                                      boost::bind(&TcpClient::handleInput, this,
                                                  boost::placeholders::_1,
                                                  boost::placeholders::_2));
    } else if (error == boost::asio::error::operation_aborted) {
        std::cout << "Server DOWN" << std::endl;
        _socket.close();
        _input.close();
    } else {
        _socket.close();
    }
}

void TcpClient::run()
{
    _socket.async_connect(
        _serverEndpoint,
        boost::bind(&TcpClient::handleWrite, this, boost::placeholders::_1));
}
