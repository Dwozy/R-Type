/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CircleCollider
*/

#ifndef CIRCLECOLLIDER_HPP_
#define CIRCLECOLLIDER_HPP_
#include "utils/Circle.hpp"

namespace GameEngine
{
    struct RectColliderComponent
    {
        Circle circle;
        std::size_t layer;
    };
}

#endif /* !CIRCLECOLLIDER_HPP_ */
