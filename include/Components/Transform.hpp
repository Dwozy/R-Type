/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Transform
*/

#ifndef TRANSFORM_HPP_
    #define TRANSFORM_HPP_
    #include "Utils/Vector.hpp"

namespace GameEngine
{

    struct TransformComponent
    {
        Vector2 velocity;
        Vector2 position;
    };

}

#endif /* !TRANSFORM_HPP_ */
