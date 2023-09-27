/*
** EPITECH PROJECT, 2023
** ClientSession.cpp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

ClientSession::ClientSession(boost::asio::io_context &IOContext):
    _socket(IOContext)
{
}

ClientSession::~ClientSession()
{
    _socket.close();
}

boost::asio::ip::tcp::socket &ClientSession::getSocket()
{
    return _socket;
}

boost::shared_ptr<ClientSession> ClientSession::get()
{
    return shared_from_this();
}

void ClientSession::handleWrite(const boost::system::error_code &error)
{
    if (!error) {
        _socket.async_read_some(boost::asio::buffer(_readBuffer),
            boost::bind(&ClientSession::handleRead,
                get(),
                boost::placeholders::_1,
                boost::placeholders::_2));
    } else {
        std::cerr << error.message() << std::endl;
    }
}

void ClientSession::handleRead(const boost::system::error_code &error, std::size_t transferredBytes)
{
    if (!error) {
        boost::asio::async_write(_socket, boost::asio::buffer(_readBuffer, transferredBytes),
            boost::bind(&ClientSession::handleWrite,
                get(),
                boost::placeholders::_1));
    } else {
        // Need to know how to tell UDP server that client has disconnected
        std::cout << "Delete " << _socket.remote_endpoint().port() << std::endl;
        std::cerr << "The client disconnected" << std::endl;
    }
}

void ClientSession::start()
{
    _socket.async_read_some(boost::asio::buffer(_readBuffer),
        boost::bind(&ClientSession::handleRead,
            get(),
            boost::placeholders::_1,
            boost::placeholders::_2));
}
