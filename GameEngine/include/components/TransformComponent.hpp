/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_
#include "utils/Vector.hpp"

namespace GameEngine
{
    struct TransformComponent
    {
        Vector2<float> position;
        Vector2<float> velocity;
    };
} // namespace GameEngine

#endif /* !TRANSFORM_HPP_ */
