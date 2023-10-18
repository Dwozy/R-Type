/*
** EPITECH PROJECT, 2023
** Communication.hpp
** File description:
** Communication
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include "../../include/RType.hpp"
#include <any>
#include <asio.hpp>
#include <iostream>

namespace GameEngine::Network
{
    class ACommunication
    {
      public:
        ACommunication(asio::io_context &IOContext, unsigned short port);
        virtual ~ACommunication(){};

        template <typename Socket, typename Endpoint>
        void sendData(void *data, std::size_t size, uint8_t packetType, Socket &socket, Endpoint &endpoint)
        {
            struct rtype::HeaderDataPacket header = {};

            header.packetType = packetType;
            header.payloadSize = size;
            this->sendInformation(data, size, socket, endpoint, header);
        };

        void sendInformation(void *data, std::size_t size, asio::ip::udp::socket &socket,
            asio::ip::udp::endpoint &endpoint, struct rtype::HeaderDataPacket &header);

        void sendInformation(void *data, std::size_t size, asio::ip::tcp::socket &socket, asio::ip::tcp::endpoint &,
            struct rtype::HeaderDataPacket &header);

      protected:
        void handleReceive(
            const asio::error_code &error, std::size_t recvBytes, struct rtype::HeaderDataPacket &header);
        void readHeader();
        virtual void handleData(const asio::error_code &error, std::size_t, struct rtype::HeaderDataPacket &header) = 0;

      protected:
        asio::streambuf _streamBuffer;
        asio::ip::udp::socket _socket;
        asio::streambuf::mutable_buffers_type _buffer;
        struct rtype::HeaderDataPacket _header;
        asio::ip::udp::endpoint _endpoint;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClient;

      private:
    };

}; // namespace GameEngine::Network

#endif /* !COMMUNICATION_HPP_ */
