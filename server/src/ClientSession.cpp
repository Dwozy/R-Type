/*
** EPITECH PROJECT, 2023
** ClientSession.cpp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

ClientSession::ClientSession(asio::io_context &IOContext,
                             SafeQueue<std::string> &clientsMessages)
    : _socket(IOContext), _clientsMessages(clientsMessages)
{
}

ClientSession::~ClientSession() { _socket.close(); }

asio::ip::tcp::socket &ClientSession::getSocket() { return _socket; }

std::shared_ptr<ClientSession> ClientSession::get()
{
    return shared_from_this();
}

void ClientSession::handleWrite(const asio::error_code &error)
{
    if (!error) {
        _socket.async_read_some(asio::buffer(_readBuffer),
                                std::bind(&ClientSession::handleRead, get(),
                                          std::placeholders::_1,
                                          std::placeholders::_2));
    } else {
        std::cerr << error.message() << std::endl;
    }
}

void ClientSession::handleRead(const asio::error_code &error,
                               std::size_t transferredBytes)
{
    if (!error) {
        std::string message;
        message += std::string(_readBuffer.begin(),
                               _readBuffer.begin() + transferredBytes);
        _clientsMessages.push(message);
        std::cout << "Add message from TCP Client" << std::endl;
        asio::async_write(_socket, asio::buffer(_readBuffer, transferredBytes),
                          std::bind(&ClientSession::handleWrite, get(),
                                    std::placeholders::_1));
    } else {
        // Need to know how to tell UDP server that client has disconnected
        // std::cout << "Delete " << _socket.remote_endpoint().port() <<
        // std::endl;
        std::cerr << "The client disconnected" << std::endl;
    }
}

void ClientSession::start()
{
    _socket.async_read_some(asio::buffer(_readBuffer),
                            std::bind(&ClientSession::handleRead, get(),
                                      std::placeholders::_1,
                                      std::placeholders::_2));
}
