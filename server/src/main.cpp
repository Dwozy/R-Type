/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "SafeQueue.hpp"
#include "TcpServer.hpp"
#include "UdpServer.hpp"

int main(int ac, char const *av[])
{
    asio::io_context IOContext;
    SafeQueue<std::string> clientsMessages;
    try {
        if (ac != 2)
            return 84;
        asio::signal_set signal(IOContext, SIGINT, SIGTERM);
        signal.async_wait(std::bind(&asio::io_service::stop, &IOContext));
        GameEngine::Network::TcpServer tcpServer(IOContext, atoi(av[1]), std::ref(clientsMessages));
        GameEngine::Network::UdpServer udpServer(IOContext, atoi(av[1]), std::ref(clientsMessages));
        IOContext.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
