/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ControllableComponent
*/

#ifndef CONTROLLABLECOMPONENT_HPP_
    #define CONTROLLABLECOMPONENT_HPP_
    #include "Keyboard.hpp"

namespace GameEngine
{
    struct ControllableComponent
    {
        GameEngine::Input::Keyboard::Key key_up;
        GameEngine::Input::Keyboard::Key key_left;
        GameEngine::Input::Keyboard::Key key_down;
        GameEngine::Input::Keyboard::Key key_right;
        float speed = 1.0f;
    };
}

#endif /* !CONTROLLABLECOMPONENT_HPP_ */
