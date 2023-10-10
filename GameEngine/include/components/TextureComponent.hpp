/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_
#include "utils/Rect.hpp"
#include "utils/SfmlTypes.hpp"
#include "utils/Vector.hpp"
#include <string>

namespace GameEngine
{
    struct TextureComponent
    {
        Texture texture;
        Sprite sprite;
        bool isRendered;
        size_t renderLayer;
    };
} // namespace GameEngine

#endif /* !TEXTURE_HPP_ */
