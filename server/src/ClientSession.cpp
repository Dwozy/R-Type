/*
** EPITECH PROJECT, 2023
** ClientSession.cpp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

ClientSession::ClientSession(boost::asio::io_context &IOContext,
                             SafeQueue<std::string> &clientsMessages)
    : _socket(IOContext), _clientsMessages(clientsMessages)
{
}

ClientSession::~ClientSession() { _socket.close(); }

boost::asio::ip::tcp::socket &ClientSession::getSocket() { return _socket; }

boost::shared_ptr<ClientSession> ClientSession::get()
{
    return shared_from_this();
}

void ClientSession::handleWrite(const boost::system::error_code &error)
{
    if (!error) {
        _socket.async_read_some(boost::asio::buffer(_readBuffer),
                                boost::bind(&ClientSession::handleRead, get(),
                                            boost::placeholders::_1,
                                            boost::placeholders::_2));
    } else {
        std::cerr << error.message() << std::endl;
    }
}

void ClientSession::handleRead(const boost::system::error_code &error,
                               std::size_t transferredBytes)
{
    if (!error) {
        std::string identity;
        identity += _socket.remote_endpoint().address().to_string();
        identity += " ";
        identity += std::to_string((int)_socket.remote_endpoint().port());
        identity += ": ";
        identity += std::string(_readBuffer.begin(),
                                _readBuffer.begin() + transferredBytes);
        _clientsMessages.push(identity);
        std::cout << "Add message from TCP Client" << std::endl;
        boost::asio::async_write(
            _socket, boost::asio::buffer(_readBuffer, transferredBytes),
            boost::bind(&ClientSession::handleWrite, get(),
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
                            boost::bind(&ClientSession::handleRead, get(),
                                        boost::placeholders::_1,
                                        boost::placeholders::_2));
}
