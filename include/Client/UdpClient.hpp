/*
** EPITECH PROJECT, 2023
** UdpClient.hpp
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "Communication.hpp"
#include "RType.hpp"
#include "Serialization.hpp"
#include <asio.hpp>
#include <iostream>

namespace Network
{
    class UdpClient
    {
      public:
        UdpClient(asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint);
        ~UdpClient();

        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint &_serverEndpoint;
        asio::io_context &_IOContext;
        asio::streambuf _streamBuffer;
        asio::streambuf::mutable_buffers_type _buffer;
        std::string _message;

      /// @brief Waiting in asynchronous operation to receive information from
      /// server
      /// @param timeout activates when exceed
      void readHeader();

      protected:
      private:
        struct rtype::HeaderDataPacket _header;
        std::unordered_map<uint8_t, std::function<void(Network::UdpClient &, uint16_t size)>> _commands;

        /// @brief Handle receive data, handling if the server is down
        /// @param error check if occured
        /// @param recvBytes corresponding the number of bytes received
        /// @param timeout activates when exceed
        // void handleReceive(const boost::system::error_code &error,
        // std::size_t recvBytes,
        //     boost::asio::deadline_timer &timeout,
        //     boost::archive::binary_iarchive &binaryArchive);
        void handleReceive(const asio::error_code &error, std::size_t recvBytes);

        /// @brief Connect to the UDP server
        void run();

        /// @brief Restart the timeout
        void handleTimeout();

        void handleData(
            const asio::error_code &error, std::size_t recvBytes, const struct rtype::HeaderDataPacket &header);
    };

    void getRoom(Network::UdpClient &, uint16_t size);
    void getString(Network::UdpClient &, uint16_t size);
} // namespace Network
#endif /* !UDPCLIENT_HPP_ */
