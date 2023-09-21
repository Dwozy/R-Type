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
    #include <asio.hpp>
    #include <array>
    #include <map>

/**
 * @brief UdpServer
 * UdpServer Class that create a UDP server that client can connect to communicate
 */
class UdpServer {
    public:
        UdpServer(asio::io_context &IOContext, int port);
        ~UdpServer();

    protected:
    private:
        asio::io_context _IOContext;
        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _clientEndpoint;
        std::array<char, 1024> _readBuffer;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClient;
        void receive();
        void sender(std::string buffer);
        void handleReceive(const asio::error_code &error, std::size_t recvBytes);
};

#endif /* !UDPSERVER_HPP_ */
