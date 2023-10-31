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
        /// @brief Abstract class that will handle communication
        /// @param IOContext that will be use to create our socket and asynchronous operation
        /// @param port that will the socket to bind
        ACommunication(asio::io_context &IOContext, unsigned short port);
        // ACommunication(asio::io_context &IOContext, unsigned short port);
        virtual ~ACommunication(){};
        /// @brief Set the header to send the value
        /// @tparam Socket Template that will be use for the socket (TCP, UDP)
        /// @tparam Endpoint Template that will be use as endpoint (TCP, UDP)
        /// @param data that will be send
        /// @param size of the data
        /// @param packetType that will be used to identified the header
        /// @param socket owner socket
        /// @param endpoint sending value to
        template <typename Socket, typename Endpoint>
        void sendData(void *data, std::size_t size, uint8_t packetType, Socket &socket, Endpoint &endpoint)
        {
            struct rtype::HeaderDataPacket header = {};

            header.packetType = packetType;
            header.payloadSize = size;
            this->sendInformation(data, size, socket, endpoint, header);
        };
        /// @brief send the data to endpoint from the socket
        /// @param data that will be send
        /// @param size of the data
        /// @param socket owner of the sending message (Udp)
        /// @param endpoint data sending to
        /// @param header that will determined the type of data
        void sendInformation(void *data, std::size_t size, asio::ip::udp::socket &socket,
            asio::ip::udp::endpoint &endpoint, struct rtype::HeaderDataPacket &header);
        /// @brief send the data to endpoint from the socket
        /// @param data that will be send
        /// @param size of the data
        /// @param socket owner of the sending message (Tcp)
        /// @param endpoint data sending to
        /// @param header that will determined the type of data
        void sendInformation(void *data, std::size_t size, asio::ip::tcp::socket &socket, asio::ip::tcp::endpoint &,
            struct rtype::HeaderDataPacket &header);
        /// @brief handle the header information
        /// @param error if asynchronous operation failed, will be checked
        /// @param recvBytes corresponding to the ammount of bytes receive
        /// @param header type of data;
        void handleReceive(
            const asio::error_code &error, std::size_t recvBytes, struct rtype::HeaderDataPacket &header);
        /// @brief read the header to retrieve informations
        void readHeader();

      protected:
        /// @brief function that will be set and used from derived class from this abstract
        virtual void handleData(struct rtype::HeaderDataPacket &, unsigned short port) = 0;

      protected:
        asio::streambuf _streamBuffer;
        asio::ip::udp::socket _udpSocket;
        asio::streambuf::mutable_buffers_type _buffer;
        struct rtype::HeaderDataPacket _header;
        asio::ip::udp::endpoint _endpoint;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClient;

      private:
    };

}; // namespace GameEngine::Network

#endif /* !COMMUNICATION_HPP_ */
