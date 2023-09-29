/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RenderableComponent
*/

#ifndef RENDERABLECOMPONENT_HPP_
    #define RENDERABLECOMPONENT_HPP_
    #include <cstdlib>

namespace GameEngine
{
    struct Renderable
    {
        bool isWorldRendered;
        size_t Renderpriority;
    };
}

#endif /* !RENDERABLECOMPONENT_HPP_ */
