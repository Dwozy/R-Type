/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GravityComponent
*/

#ifndef GRAVITYCOMPONENT_HPP_
#define GRAVITYCOMPONENT_HPP_
#include "utils/Vector.hpp"

namespace GameEngine
{
    struct GravityComponent
    {
        Vector2<float> gravityForce;
        bool isActive;
    };
}

#endif /* !GRAVITYCOMPONENT_HPP_ */
