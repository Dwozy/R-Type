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
    #include <boost/bind.hpp>
    // #include <boost/signals2.hpp>

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
        void handleReceive(const boost::system::error_code &error, std::size_t recvBytes);
        void sender(const boost::system::error_code &error);
        void receive();
        void run();
};

#endif /* !UDPCLIENT_HPP_ */
