/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PressableComponent
*/

#ifndef PRESSABLECOMPONENT_HPP_
#define PRESSABLECOMPONENT_HPP_
#include <functional>
#include "utils/Rect.hpp"

namespace GameEngine
{
    enum PressableState
    {
        defaultState,
        hoveredState,
        pressedState,
    };

    struct PressableComponent
    {
        Recti hitbox;
        Recti textureDefault;
        Recti textureHovered;
        Recti texturePressed;
        PressableState state;
        std::function<void()> action;
    };
} // namespace GameEngine

#endif /* !PRESSABLECOMPONENT_HPP_ */
