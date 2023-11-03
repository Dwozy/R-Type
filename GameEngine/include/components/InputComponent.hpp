/*
** EPITECH PROJECT, 2023
** InputComponent.hpp
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_
#include <cstdint>
#include <map>
#include "Keyboard.hpp"

namespace GameEngine
{
    struct InputComponent
    {
        std::map<Input::InputType, Input::Keyboard::Key> inputs;

        void addInput(Input::InputType inputType, Input::Keyboard::Key key)
        {
            inputs.insert({inputType, key});
        };
    };
} // namespace GameEngine
#endif /* !INPUTCOMPONENT_HPP_ */
