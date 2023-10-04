/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RectCollider
*/

#ifndef RECTCOLLIDER_HPP_
#define RECTCOLLIDER_HPP_
#include "utils/Rect.hpp"
#include <cstdlib>

namespace GameEngine
{
    struct RectColliderComponent
    {
        Rect<float> rect;
        std::size_t layer;
    };
} // namespace GameEngine

#endif /* !RECTCOLLIDER_HPP_ */
