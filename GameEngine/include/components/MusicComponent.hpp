/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Music
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_
    #include <string>
    #include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    struct MusicComponent
    {
        std::string path;
        Music music;
    };
}

#endif /* !MUSIC_HPP_ */
