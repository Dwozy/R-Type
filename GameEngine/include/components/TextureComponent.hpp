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
    #include "utils/Rect.hpp"

namespace GameEngine
{
    struct TextureComponent
    {
        Texture texture;
        Sprite sprite;
        bool isRendered;
        size_t renderLayer;
    };
}

#endif /* !TEXTURE_HPP_ */
