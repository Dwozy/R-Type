/*
** EPITECH PROJECT, 2023
** TcpServer.hpp
** File description:
** TcpServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include "ClientSession.hpp"
#include "SafeQueue.hpp"
#include <asio.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <thread>

namespace Network
{

    /// @brief This class manages all the TCP server event from clients
    class TcpServer
    {
      public:
        TcpServer(boost::asio::io_context &IOContext, int port,
                  SafeQueue<std::string> &clientsMessages);
        ~TcpServer();

      protected:
      private:
        /// @brief Accept a client when trying to connect
        /// @param clientSession Variable that will start a new client session
        void accept(boost::shared_ptr<ClientSession> clientSession);

        /// @brief Handle the connected client by starting its session
        /// @param clientSession the client session
        /// @param error The error that can occured when client disconnect
        void handleAccept(boost::shared_ptr<ClientSession> clientSession,
                          const boost::system::error_code &error);

        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::ip::tcp::socket _socket;
        boost::asio::io_context &_IOContext;
        int _port;
        SafeQueue<std::string> &_clientsMessages;
        boost::asio::ip::tcp::endpoint _clientEndpoint;
        std::size_t count;
        std::array<char, 1024> _readBuffer;
        std::vector<boost::shared_ptr<ClientSession>> _clients;
    };
} // namespace Network

#endif /* !TCPSERVER_HPP_ */
