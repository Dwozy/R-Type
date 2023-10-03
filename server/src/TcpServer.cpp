/*
** EPITECH PROJECT, 2023
** TcpServer.cpp
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

Network::TcpServer::TcpServer(asio::io_context &IOContext, int port,
                              SafeQueue<std::string> &clientsMessages)
    : _acceptor(IOContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
      _socket(IOContext), _IOContext(IOContext), _port(port),
      _clientsMessages(clientsMessages)
{
    std::shared_ptr<ClientSession> clientSession =
        std::make_shared<ClientSession>(_IOContext, _clientsMessages);
    accept(clientSession);
}

void Network::TcpServer::accept(std::shared_ptr<ClientSession> clientSession)
{
    _acceptor.async_accept(clientSession->getSocket(),
                           std::bind(&Network::TcpServer::handleAccept, this,
                                     clientSession, std::placeholders::_1));
}

Network::TcpServer::~TcpServer() { _socket.close(); }

void Network::TcpServer::handleAccept(
    std::shared_ptr<ClientSession> clientSession, const asio::error_code &error)
{
    if (!error) {
        std::cout << "New Client connected" << std::endl;
        clientSession->start();
        clientSession =
            std::make_shared<ClientSession>(_IOContext, _clientsMessages);
        _acceptor.async_accept(clientSession->getSocket(),
                               std::bind(&Network::TcpServer::handleAccept,
                                         this, clientSession,
                                         std::placeholders::_1));
    } else {
        std::cerr << "The client disconnected" << std::endl;
    }
}
