/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "UdpClient.hpp"

int main(int ac, char const *av[]) {
    try {
        if (ac != 3)
            return 84;
        boost::asio::io_context ioContext;
        boost::asio::ip::udp::endpoint serverUdpEndpoint(boost::asio::ip::address::from_string(av[1]), atoi(av[2]));
        // boost::asio::ip::tcp::endpoint serverTcpEndpoint(boost::asio::ip::address::from_string(av[1]), atoi(av[2]));
        UdpClient udpClient(ioContext, serverUdpEndpoint);
        ioContext.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
