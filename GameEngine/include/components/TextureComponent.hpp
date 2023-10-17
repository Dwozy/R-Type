/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
    #define TEXTURE_HPP_
    #include "utils/Vector.hpp"
    #include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    struct TextureComponent
    {
        Texture texture;
        Sprite sprite;
        bool animated;
        std::vector<Rect<int>> textureRects;
        float animationSpeed;
        bool isRendered;
        float lastUpdate;
        size_t animeid;
        size_t renderLayer;
    };
} // namespace GameEngine

#endif /* !TEXTURE_HPP_ */
