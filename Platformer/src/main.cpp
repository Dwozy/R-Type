/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** main
*/

#include "Platformer.hpp"

int main(int ac, char const *av[])
{
    try {
        Platformer game;
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
