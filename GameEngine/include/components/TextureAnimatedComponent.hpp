/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** TextureAnimatedComponent
*/

#ifndef TEXTUREANIMATEDCOMPONENT_HPP_
    #define TEXTUREANIMATEDCOMPONENT_HPP_
    #include "utils/Vector.hpp"
    #include "utils/SfmlTypes.hpp"
    #include "utils/DeltaTime.hpp"
    #include <chrono>

    namespace GameEngine
    {
        struct TextureAnimatedComponent
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


#endif /* !TEXTUREANIMATEDCOMPONENT_HPP_ */
