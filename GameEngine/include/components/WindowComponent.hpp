/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_
#include "utils/SfmlTypes.hpp"
#include "utils/Vector.hpp"

namespace GameEngine
{
    struct WindowComponent
    {
        Vector2<int> size;
        Window window;
    };
} // namespace GameEngine

#endif /* !WINDOW_HPP_ */
