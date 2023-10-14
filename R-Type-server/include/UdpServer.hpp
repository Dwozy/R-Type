/*
** EPITECH PROJECT, 2023
** UdpServer.hpp
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "Network/Server/ACommunication.hpp"
#include "RType.hpp"
#include "SafeQueue.hpp"
#include "Serialization.hpp"
#include <array>
#include <asio.hpp>
#include <iostream>
#include <map>

namespace RType::Server
{

    /// @brief UdpServer Class that create a UDP server that client can connect
    /// to communicate
    class UdpServer : public GameEngine::Network::ACommunication
    {
      public:
        UdpServer(asio::io_context &IOContext, unsigned short port, SafeQueue<std::string> &clientMessages);
        ~UdpServer();

        void handleData(const asio::error_code &error, std::size_t, const struct rtype::HeaderDataPacket &header);

        std::map<unsigned short, asio::ip::udp::endpoint> getListClients();

        /// @brief Sender function that will send to message to the client
        void broadcastInformation();

        void handleRoom(uint16_t);
        void handleEntity(uint16_t);
        void handleString(uint16_t);
        void handleConnexion(uint16_t);

      protected:
      private:

        /// @brief Update information to clients at periodical interval
        void updateGameInfo();

        /// @brief Update information from TCP server
        void updateTCPInformation();

        asio::steady_timer _timer;
        asio::steady_timer _timerTCP;
        asio::signal_set _signal;
        SafeQueue<std::string> &_clientsMessages;
        asio::ip::udp::endpoint _clientEndpoint;
        std::unordered_map<uint8_t, std::function<void(uint16_t size)>> _commands;
        std::map<unsigned short, struct rtype::Entity> _listPlayersInfos;
        unsigned short indexPlayer;

    };
} // namespace GameEngine::Network
#endif /* !UDPSERVER_HPP_ */
