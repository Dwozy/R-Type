/*
** EPITECH PROJECT, 2023
** UdpServer.hpp
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
    #define UDPSERVER_HPP_

    #include <iostream>
    #include <boost/bind/bind.hpp>
    #include <boost/asio.hpp>
    #include <array>
    #include <map>

namespace Network {

    /// @brief UdpServer Class that create a UDP server that client can connect to communicate
    class UdpServer {
        public:
            UdpServer(boost::asio::io_context &IOContext, int port);
            ~UdpServer();

        protected:
        private:
            /// @brief Waiting for a message from a client
            void receive();

            /// @brief Sender function that will send to message to the client
            /// @param buffer corresponding to the message that will be send to the client
            void sender(std::string buffer);
            void sender();

            /// @brief Receive the message from a client that achieve to connect to the UDP server
            /// @param error Error from the asynchronous waiting message
            /// @param recvBytes corresponding to the number of bytes received
            void handleReceive(const boost::system::error_code &error, std::size_t recvBytes);

            /// @brief Start the timer to broadcast informations to all clients at periodical interval.
            void startTimer();

            boost::asio::ip::udp::socket _socket;
            boost::asio::io_context &_IOContext;
            boost::asio::deadline_timer _timer;
            std::map<unsigned short, boost::asio::ip::udp::endpoint> _listClient;
            boost::asio::ip::udp::endpoint _clientEndpoint;
            std::array<char, 1024> _readBuffer;
    };
}
#endif /* !UDPSERVER_HPP_ */
