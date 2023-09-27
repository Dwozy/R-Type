/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Music
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_
    #include <string>
    #include "utils/Vector.hpp"
    #include "utils/sfmlTypes.hpp"

namespace GameEngine {

    struct Music {
        SFMusic music;
        std::string path;
    };
}

#endif /* !MUSIC_HPP_ */
