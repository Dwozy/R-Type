/*
** EPITECH PROJECT, 2023
** Client.hpp
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <boost/asio.hpp>

class Client {
    public:
        Client(boost::asio::io_context &IOContext,
            boost::asio::ip::udp::endpoint &serverUdpEndpoint,
            boost::asio::ip::tcp::endpoint &serverTcpEndpoint);
        ~Client();

    protected:
    private:
        boost::asio::ip::udp::socket _serverUdpSocket;
        boost::asio::ip::tcp::socket _serverTcpSocket;
        boost::asio::ip::udp::endpoint &_serverUdpEndpoint;
        boost::asio::ip::tcp::endpoint &_serverTcpEndpoint;
};

#endif /* !CLIENT_HPP_ */
