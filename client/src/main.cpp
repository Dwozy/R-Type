/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <asio.hpp>
#include <boost/thread.hpp>
#include <iostream>

int main(int ac, char const *av[])
{
    try {
        if (ac != 3)
            return 84;
        asio::io_context IOContext;
        asio::signal_set signal(IOContext, SIGINT, SIGTERM);
        signal.async_wait(std::bind(&asio::io_service::stop, &IOContext));
        asio::ip::udp::endpoint serverUdpEndpoint(
            asio::ip::address::from_string(av[1]), atoi(av[2]));
        asio::ip::tcp::endpoint serverTcpEndpoint(
            asio::ip::address::from_string(av[1]), atoi(av[2]));
        UdpClient udpClient(IOContext, serverUdpEndpoint);
        TcpClient tcpClient(IOContext, serverTcpEndpoint);
        IOContext.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
