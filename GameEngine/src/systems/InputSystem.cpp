/*
** EPITECH PROJECT, 2023
** InputSystem.cpp
** File description:
** InputSystem
*/

#include "systems/InputSystem.hpp"
#include "Event.hpp"
#include "Keyboard.hpp"

namespace GameEngine
{
    void InputSystem::handleInput(std::size_t id, std::pair<Input::InputType, Input::Keyboard::Key> inputInfo)
    {
        struct Input::InputInfo data = {.id = id, .idInput = inputInfo.first};
        if (InputManager::isKeyPressed(inputInfo.second)) {
            data.state = true;
            _eventManager.getHandler<struct Input::InputInfo>(static_cast<EventType>(Event::SendInput)).publish(data);
        }
        if (InputManager::isKeyReleased(inputInfo.second)) {
            data.state = false;
            _eventManager.getHandler<struct Input::InputInfo>(static_cast<EventType>(Event::SendInput)).publish(data);
        }
    }

    void InputSystem::operator()(SparseArray<InputComponent> &inputs)
    {
        for (std::size_t i = 0; i < inputs.size(); i++) {
            auto &input = inputs[i];
            if (!input)
                continue;
            for (auto inputInfo : input.value().inputs)
                handleInput(i, inputInfo);
        }
    }
} // namespace GameEngine
