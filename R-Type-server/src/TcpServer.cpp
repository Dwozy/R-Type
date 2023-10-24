/*
** EPITECH PROJECT, 2023
** TcpServer.cpp
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

RType::Server::TcpServer::TcpServer(asio::io_context &IOContext, int port)
    : _acceptor(IOContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), _socket(IOContext),
      _IOContext(IOContext)
{
}

RType::Server::TcpServer::~TcpServer() { _socket.close(); }

void RType::Server::TcpServer::accept(std::shared_ptr<ClientSession> clientSession)
{
    _acceptor.async_accept(clientSession->getSocket(),
        std::bind(&RType::Server::TcpServer::handleAccept, this, clientSession, std::placeholders::_1));
}

void RType::Server::TcpServer::handleAccept(std::shared_ptr<ClientSession> clientSession, const asio::error_code &error)
{
    if (!error) {
        _clients.push_back(clientSession);
        std::cout << "New Client connected" << std::endl;
        clientSession->start();
        clientSession = std::make_shared<ClientSession>(_IOContext);
        _acceptor.async_accept(clientSession->getSocket(),
            std::bind(&RType::Server::TcpServer::handleAccept, this, clientSession, std::placeholders::_1));
    } else {
        std::cerr << "The client disconnected" << std::endl;
    }
}

void RType::Server::TcpServer::run()
{
    std::shared_ptr<ClientSession> clientSession = std::make_shared<ClientSession>(_IOContext);
    accept(clientSession);
}
