/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** InputSystem
*/

#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "components/InputComponent.hpp"
#include "Keyboard.hpp"

namespace GameEngine
{
    class InputSystem
    {
      public:
        InputSystem(EventManager &eventManager) : _eventManager(eventManager){};
        ~InputSystem() = default;

        void operator()(SparseArray<InputComponent> &inputs);
        void handleInput(
            std::size_t id, std::pair<Input::InputType, Input::Keyboard::Key> inputInfo);

      private:
        EventManager &_eventManager;
    };
} // namespace GameEngine

#endif /* !InputSystem_HPP_ */
