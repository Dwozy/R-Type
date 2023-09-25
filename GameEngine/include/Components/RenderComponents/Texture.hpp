/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
    #define TEXTURE_HPP_
    #include <string>
    #include "utils/Vector.hpp"
    #include "utils/sfmlTypes.hpp"

namespace GameEngine
{
    struct Texture
    {
        std::string path;
        Vector2<int> position;
        GameEngine::Texture texture;
    };
}

#endif /* !TEXTURE_HPP_ */
