/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <asio.hpp>
#include <iostream>
#include "RTypeClient.hpp"

int main(int ac, char const *av[])
{
    if (ac == 3 && atoi(av[2]) != 0)
        RType::Client::RTypeClient client(av[1], atoi(av[2]));
    else
        RType::Client::RTypeClient client;
    try {
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
