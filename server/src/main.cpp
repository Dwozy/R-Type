/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "UdpServer.hpp"

int main(int ac, char const *av[])
{
    asio::io_context io_context;
    try {
        if (ac != 2)
            return 84;
        UdpServer server(io_context, atoi(av[1]));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
