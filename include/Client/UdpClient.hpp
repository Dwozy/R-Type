/*
** EPITECH PROJECT, 2023
** UdpClient.hpp
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
    #define UDPCLIENT_HPP_

    #include <iostream>
    #include <boost/asio.hpp>
    #include <boost/bind/bind.hpp>

class UdpClient {
    public:
        UdpClient(boost::asio::io_context &IOContext, boost::asio::ip::udp::endpoint &serverEndpoint);
        ~UdpClient();

    protected:
    private:
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint &_serverEndpoint;
        boost::asio::io_context &_IOContext;
        std::array<char, 1024> _readBuffer;

        /// @brief Handle receive data, handling if the server is down
        /// @param error check if occured
        /// @param recvBytes corresponding the number of bytes received
        /// @param timeout activates when exceed
        void handleReceive(const boost::system::error_code &error, std::size_t recvBytes,
            boost::asio::deadline_timer &timeout);

        /// @brief Waiting in asynchronous operation to receive information from server
        /// @param timeout activates when exceed
        void receive(boost::asio::deadline_timer &timeout);

        /// @brief Connect to the UDP server
        void run();

        /// @brief Restart the timeout
        void handleTimeout();

};

#endif /* !UDPCLIENT_HPP_ */
