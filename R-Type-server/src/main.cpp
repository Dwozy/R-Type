/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include "RTypeServer.hpp"
#include <iostream>

int main(int ac, char const *av[])
{
    try {
        if (ac == 2 && atoi(av[1]) != 0)
            RType::Server::RTypeServer server(atoi(av[1]));
        else
            RType::Server::RTypeServer server;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
