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
        void sendData(void *data, std::size_t size, uint8_t packetType, asio::ip::udp::socket &socket,
            asio::ip::udp::endpoint &clientEndpoint)
        {
            struct rtype::HeaderDataPacket header;

            header.packetType = packetType;
            header.payloadSize = size;

            socket.async_send_to(asio::buffer(&header, sizeof(header)), clientEndpoint,
                [&](const asio::error_code &error, std::size_t sendBytes) {
                    if (!error) {
                        std::cout << "Send : " << sendBytes << " bytes as header." << std::endl;
                    }
                });
            socket.async_send_to(
                asio::buffer(data, size), clientEndpoint, [&](const asio::error_code &error, std::size_t sendBytes) {
                    if (!error)
                        std::cout << "Send : " << sendBytes << " bytes as data." << std::endl;
                });
        }
    };

}; // namespace Network

#endif /* !COMMUNICATION_HPP_ */
