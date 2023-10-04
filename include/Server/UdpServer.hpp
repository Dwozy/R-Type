/*
** EPITECH PROJECT, 2023
** UdpServer.hpp
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "RType.hpp"
#include "SafeQueue.hpp"
#include <array>
#include <asio.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <iostream>
#include <map>

namespace Network
{

    /// @brief UdpServer Class that create a UDP server that client can connect
    /// to communicate
    class UdpServer
    {
      public:
        UdpServer(asio::io_context &IOContext, int port,
                  SafeQueue<std::string> &clientsMessages);
        ~UdpServer();

      protected:
      private:
        /// @brief Waiting for a message from a client
        void receive();

        /// @brief Sender function that will send to message to the client
        void sender();

        /// @brief Receive the message from a client that achieve to connect to
        /// the UDP server
        /// @param error Error from the asynchronous waiting message
        /// @param recvBytes corresponding to the number of bytes received
        void handleReceive(const asio::error_code &error,
                           std::size_t recvBytes);

        /// @brief Update information to clients at periodical interval
        void updateGameInfo();

        /// @brief Update information from TCP server
        void updateTCPInformation();

        void sendHeader(std::size_t size, const asio::ip::udp::endpoint &clientEndpoint);

        template<typename Data>
        void sendArchiveData(Data data, const asio::ip::udp::endpoint &clientEndpoint)
        {
            asio::streambuf streamBuffer;
            std::ostream os(&streamBuffer);
            boost::archive::binary_oarchive binaryArchive(os);

            binaryArchive << data;
            _socket.send_to(streamBuffer.data(), clientEndpoint);
        }

        template<typename Data>
        uint16_t getArchiveDataSize(Data data)
        {
            asio::streambuf streamBuffer;
            std::ostream os(&streamBuffer);
            boost::archive::binary_oarchive binaryArchive(os);

            binaryArchive << data;
            return streamBuffer.data().size();
        }

        asio::ip::udp::socket _socket;
        asio::io_context &_IOContext;
        asio::steady_timer _timer;
        asio::steady_timer _timerTCP;
        SafeQueue<std::string> &_clientsMessages;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClient;
        asio::ip::udp::endpoint _clientEndpoint;
        std::array<char, 1024> _readBuffer;
    };
} // namespace Network
#endif /* !UDPSERVER_HPP_ */
