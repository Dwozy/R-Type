/*
** EPITECH PROJECT, 2023
** ClientSession.cpp
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

RType::Server::ClientSession::ClientSession(asio::io_context &IOContext) : _socket(IOContext) {}

RType::Server::ClientSession::~ClientSession() { _socket.close(); }

asio::ip::tcp::socket &RType::Server::ClientSession::getSocket() { return _socket; }

std::shared_ptr<RType::Server::ClientSession> RType::Server::ClientSession::get() { return shared_from_this(); }

void RType::Server::ClientSession::handleWrite(const asio::error_code &error)
{
    if (!error) {
        _socket.async_read_some(asio::buffer(_readBuffer),
            std::bind(&RType::Server::ClientSession::handleRead, get(), std::placeholders::_1, std::placeholders::_2));
    } else {
        std::cerr << error.message() << std::endl;
    }
}

void RType::Server::ClientSession::handleRead(const asio::error_code &error, std::size_t transferredBytes)
{
    if (!error) {
        std::string message;
        message += std::string(_readBuffer.begin(), _readBuffer.begin() + transferredBytes);
        // _clientsMessages.push(message);
        asio::async_write(_socket, asio::buffer(_readBuffer, transferredBytes),
            std::bind(&RType::Server::ClientSession::handleWrite, get(), std::placeholders::_1));
    } else {
        std::cerr << "The client disconnected" << std::endl;
    }
}

void RType::Server::ClientSession::start()
{
    _socket.async_read_some(asio::buffer(_readBuffer),
        std::bind(&RType::Server::ClientSession::handleRead, get(), std::placeholders::_1, std::placeholders::_2));
}
