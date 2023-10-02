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
        Input::Keyboard::Key key_up;
        Input::Keyboard::Key key_left;
        Input::Keyboard::Key key_down;
        Input::Keyboard::Key key_right;
        float speed = 1.0f;
    };
}

#endif /* !CONTROLLABLECOMPONENT_HPP_ */
