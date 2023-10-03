/*
** EPITECH PROJECT, 2023
** UdpClient.hpp
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
    #define UDPCLIENT_HPP_

    #include <iostream>
    #include <boost/bind/bind.hpp>
    #include <boost/asio.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include "RType.hpp"

class UdpClient {
    public:
        UdpClient(boost::asio::io_context &IOContext, boost::asio::ip::udp::endpoint &serverEndpoint);
        ~UdpClient();

    protected:
    private:
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint &_serverEndpoint;
        boost::asio::io_context &_IOContext;
        std::istream _is;
        struct rtype::HeaderDataPacket _header;
        boost::asio::streambuf _streamBuffer;
        std::array<char, 1024> _readBuffer;

        /// @brief Handle receive data, handling if the server is down
        /// @param error check if occured
        /// @param recvBytes corresponding the number of bytes received
        /// @param timeout activates when exceed
        // void handleReceive(const boost::system::error_code &error, std::size_t recvBytes,
        //     boost::asio::deadline_timer &timeout, boost::archive::binary_iarchive &binaryArchive);
        void handleReceive(const boost::system::error_code &error, std::size_t recvBytes);

        /// @brief Waiting in asynchronous operation to receive information from server
        /// @param timeout activates when exceed
        void receive();

        /// @brief Connect to the UDP server
        void run();

        /// @brief Restart the timeout
        void handleTimeout();

        /// @brief Read data from a header
        void readData(const struct rtype::HeaderDataPacket header);
};

#endif /* !UDPCLIENT_HPP_ */
