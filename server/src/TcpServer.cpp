/*
** EPITECH PROJECT, 2023
** TcpServer.cpp
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

Network::TcpServer::TcpServer(boost::asio::io_context &IOContext, int port,
                              SafeQueue<std::string> &clientsMessages)
    : _acceptor(IOContext, boost::asio::ip::tcp::endpoint(
                               boost::asio::ip::tcp::v4(), port)),
      _socket(IOContext), _IOContext(IOContext), _port(port),
      _clientsMessages(clientsMessages)
{
    boost::shared_ptr<ClientSession> clientSession =
        boost::make_shared<ClientSession>(_IOContext, _clientsMessages);
    accept(clientSession);
}

Network::TcpServer::~TcpServer() { _socket.close(); }

void Network::TcpServer::handleAccept(
    boost::shared_ptr<ClientSession> clientSession,
    const boost::system::error_code &error)
{
    if (!error) {
        std::cout << "New Client connected" << std::endl;
        clientSession->start();
        clientSession =
            boost::make_shared<ClientSession>(_IOContext, _clientsMessages);
        _acceptor.async_accept(clientSession->getSocket(),
                               boost::bind(&Network::TcpServer::handleAccept,
                                           this, clientSession,
                                           boost::placeholders::_1));
    } else {
        std::cerr << "The client disconnected" << std::endl;
    }
}

void Network::TcpServer::accept(boost::shared_ptr<ClientSession> clientSession)
{
    _acceptor.async_accept(clientSession->getSocket(),
                           boost::bind(&Network::TcpServer::handleAccept, this,
                                       clientSession, boost::placeholders::_1));
}
