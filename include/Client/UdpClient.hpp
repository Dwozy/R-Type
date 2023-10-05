/*
** EPITECH PROJECT, 2023
** UdpClient.hpp
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "RType.hpp"
#include <asio.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

namespace Network
{
    class UdpClient
    {
      public:
        UdpClient(asio::io_context &IOContext,
                  asio::ip::udp::endpoint &serverEndpoint);
        ~UdpClient();

        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint &_serverEndpoint;
        asio::io_context &_IOContext;
        std::istream _is;
        asio::streambuf _streamBuffer;

      protected:
      private:
        std::istream _isHeader;
        asio::streambuf _streamBufferHeader;
        asio::streambuf::mutable_buffers_type _buffer;
        struct rtype::HeaderDataPacket _header;
        std::array<char, 1024> _readBuffer;
        std::unordered_map<std::size_t, std::function<void(Network::UdpClient &,
                                                           uint16_t size)>>
            _commands;

        /// @brief Handle receive data, handling if the server is down
        /// @param error check if occured
        /// @param recvBytes corresponding the number of bytes received
        /// @param timeout activates when exceed
        // void handleReceive(const boost::system::error_code &error,
        // std::size_t recvBytes,
        //     boost::asio::deadline_timer &timeout,
        //     boost::archive::binary_iarchive &binaryArchive);
        void handleReceive(const asio::error_code &error,
                           std::size_t recvBytes);

        /// @brief Waiting in asynchronous operation to receive information from
        /// server
        /// @param timeout activates when exceed
        void readHeader();

        /// @brief Connect to the UDP server
        void run();

        /// @brief Restart the timeout
        void handleTimeout();

        /// @brief Read data from a header
        void readData(const struct rtype::HeaderDataPacket header);

        void handleData(const struct rtype::HeaderDataPacket &header);
    };

    void getRoom(Network::UdpClient &, uint16_t size);
    void getString(Network::UdpClient &, uint16_t size);
} // namespace Network
#endif /* !UDPCLIENT_HPP_ */
