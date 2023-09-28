/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "UdpServer.hpp"
#include "TcpServer.hpp"
#include "SafeQueue.hpp"

int main(int ac, char const *av[])
{
    boost::asio::io_context IOContext;
    SafeQueue<std::string> clientsMessages;
    try {
        if (ac != 2)
            return 84;
        boost::asio::signal_set signal(IOContext, SIGINT, SIGTERM);
        signal.async_wait(boost::bind(&boost::asio::io_service::stop, &IOContext));
        Network::TcpServer tcpServer(IOContext, atoi(av[1]), std::ref(clientsMessages));
        Network::UdpServer udpServer(IOContext, atoi(av[1]), std::ref(clientsMessages));
        IOContext.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
