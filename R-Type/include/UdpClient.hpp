/*
** EPITECH PROJECT, 2023
** UdpClient.hpp
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "ACommunication.hpp"
#include "RType.hpp"
#include "Serialization.hpp"
#include <asio.hpp>
#include <iostream>

namespace RType::Client
{
    class UdpClient : public GameEngine::Network::ACommunication
    {
      public:
        UdpClient(asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint);
        ~UdpClient();

        void handleRoom(uint16_t size);
        void handleString(uint16_t size);
        void handleEntity(uint16_t size);

        asio::io_context &_IOContext;
        asio::ip::udp::endpoint &_serverEndpoint;

      protected:
      private:
        struct rtype::HeaderDataPacket _header;
        std::unordered_map<uint8_t, std::function<void(uint16_t)>> _commands;
        std::map<unsigned short, struct rtype::Entity> _listPlayersInfos;

        /// @brief Connect to the UDP server
        void run();

        void handleData(
            const asio::error_code &error, std::size_t recvBytes, const struct rtype::HeaderDataPacket &header);
    };
} // namespace RType::Client
#endif /* !UDPCLIENT_HPP_ */
