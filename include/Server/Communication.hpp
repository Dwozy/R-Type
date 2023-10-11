/*
** EPITECH PROJECT, 2023
** Communication.hpp
** File description:
** Communication
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include "RType.hpp"
#include <asio.hpp>
#include <iostream>

namespace Network
{
    class Communication
    {
      public:
        template <typename Socket, typename Endpoint>
        void sendData(void *data, std::size_t size, uint8_t packetType, Socket &socket, Endpoint &clientEndpoint)
        {
            struct rtype::HeaderDataPacket header;

            header.packetType = packetType;
            header.payloadSize = size;
            sendInformation(data, size, socket, clientEndpoint, header);
        }

        void sendInformation(void *data, std::size_t size, asio::ip::udp::socket &socket,
            asio::ip::udp::endpoint &clientEndpoint, struct rtype::HeaderDataPacket header);

        void sendInformation(void *data, std::size_t size, asio::ip::tcp::socket &socket, asio::ip::tcp::endpoint &,
            struct rtype::HeaderDataPacket header);

        inline void receiveData();
    };

}; // namespace Network

#endif /* !COMMUNICATION_HPP_ */
