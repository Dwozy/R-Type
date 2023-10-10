/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_
#include "utils/SfmlTypes.hpp"
#include <string>

namespace GameEngine
{
    struct MusicComponent
    {
        std::string path;
        Music music;
    };
} // namespace GameEngine

#endif /* !MUSIC_HPP_ */
