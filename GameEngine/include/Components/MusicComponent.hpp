/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Music
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_
    #include <string>
    #include "utils/sfmlTypes.hpp"

namespace GameEngine
{
    struct Music
    {
        std::string path;
        SFMusic music;
    };
}

#endif /* !MUSIC_HPP_ */
