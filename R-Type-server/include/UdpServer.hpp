/*
** EPITECH PROJECT, 2023
** UdpServer.hpp
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "Network/ACommunication.hpp"
#include "RType.hpp"
#include "SafeQueue.hpp"
#include "Network/Serialization.hpp"
#include <array>
#include <asio.hpp>
#include <iostream>
#include <map>
#include "Entity.hpp"

namespace RType::Server
{
    /// @brief UdpServer Class that create a UDP server that client can connect
    /// to communicate
    class UdpServer : public GameEngine::Network::ACommunication
    {
      public:
        UdpServer(asio::io_context &IOContext, unsigned short port, SafeQueue<struct rtype::Event> &eventQueue);
        ~UdpServer();

        void handleData(const asio::error_code &error, std::size_t, struct rtype::HeaderDataPacket &header);

        std::map<unsigned short, asio::ip::udp::endpoint> getListClients();

        /// @brief Sender function that will send to message to the client
        void broadcastInformation(uint8_t packetType, std::vector<std::byte> dataToSend);

        void handleRoom(struct rtype::HeaderDataPacket header);
        void handleEntity(struct rtype::HeaderDataPacket header);
        void handleString(struct rtype::HeaderDataPacket header);

        void handleMove(struct rtype::HeaderDataPacket header);
        void handleConnexion(struct rtype::HeaderDataPacket header);
        void handleDisconnexion(struct rtype::HeaderDataPacket header);

        void run();

      protected:
      private:
        /// @brief Update information to clients at periodical interval
        void updateGameInfo();

        /// @brief Update information from TCP server
        void updateTCPInformation();

        unsigned short indexPlayer;
        asio::steady_timer _timer;
        asio::steady_timer _timerTCP;
        asio::signal_set _signal;
        SafeQueue<struct rtype::Event> &_eventQueue;
        asio::ip::udp::endpoint _clientEndpoint;
        std::unordered_map<uint8_t, std::function<void(struct rtype::HeaderDataPacket)>> _commands;
        // std::map<unsigned short, struct rtype::Entity> _listPlayersInfos;
        std::map<unsigned short, struct rtype::Entity> _listPlayersInfos;
    };
} // namespace RType::Server
#endif /* !UDPSERVER_HPP_ */
