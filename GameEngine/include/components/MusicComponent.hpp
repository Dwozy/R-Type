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
#include <memory>

namespace GameEngine
{
    struct MusicComponent
    {
        std::string path;
        std::shared_ptr<Music> music;
        // Music music;
    };
} // namespace GameEngine

#endif /* !MUSIC_HPP_ */
