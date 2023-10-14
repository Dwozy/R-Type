/*
** EPITECH PROJECT, 2023
** RTypeServer.hpp
** File description:
** RTypeServer
*/

#ifndef RTYPESERVER_HPP_
#define RTYPESERVER_HPP_

#include "RType.hpp"
#include "SafeQueue.hpp"
#include "UdpServer.hpp"
#include <asio.hpp>

namespace RType::Server
{
    class RTypeServer
    {
      public:
        RTypeServer(unsigned short port = 8080);
        ~RTypeServer();

        void gameLoop();

        void communication(RType::Server::UdpServer &udpserver);

      protected:
      private:
        asio::io_context _IOContext;
        asio::signal_set _signal;
        SafeQueue<std::string> _clientsMessages;
        RType::Server::UdpServer _udpServer;
        std::map<struct rtype::Room, std::map<unsigned short, struct rtype::Entity>> _listPlayersInfos;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClients;
    };
} // namespace RType::Server
#endif /* !RTYPESERVER_HPP_ */
