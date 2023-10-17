/*
** EPITECH PROJECT, 2023
** UdpClient.hpp
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "Network/ACommunication.hpp"
#include "RType.hpp"
#include "Serialization.hpp"
#include <asio.hpp>
#include <iostream>
#include "SafeQueue.hpp"

namespace RType::Client
{
    class UdpClient : public GameEngine::Network::ACommunication
    {
      public:
        UdpClient(asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint, SafeQueue<struct rtype::Event> &eventQueue);
        ~UdpClient();

        void handleRoom(struct rtype::HeaderDataPacket header);
        void handleString(struct rtype::HeaderDataPacket header);
        void handleEntity(struct rtype::HeaderDataPacket header);
        void handleConnexionSuccess(struct rtype::HeaderDataPacket header);

        void run();

      protected:
      private:
        asio::io_context &_IOContext;
        asio::ip::udp::endpoint &_serverEndpoint;
        struct rtype::HeaderDataPacket _header;
        std::unordered_map<uint8_t, std::function<void(struct rtype::HeaderDataPacket header)>> _commands;
        std::map<unsigned short, struct rtype::Entity> _listPlayersInfos;
        SafeQueue<struct rtype::Event> &_eventQueue;

        /// @brief Connect to the UDP server

        void handleData(
            const asio::error_code &error, std::size_t recvBytes, const struct rtype::HeaderDataPacket &header);
    };
} // namespace RType::Client
#endif /* !UDPCLIENT_HPP_ */
