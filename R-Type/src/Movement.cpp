/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Movement
*/

#include "RTypeClient.hpp"
#include <iostream>

namespace RType::Client
{
    void RTypeClient::updatePlayerMovement(const GameEngine::TransformComponent &transform)
    {
        std::cout << "transform velocity:" << transform.velocity.x << " " << transform.velocity.y << std::endl;
    }

    void RTypeClient::handlePlayerMovement()
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        if ((GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Z) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Up) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::S) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Down) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Q) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Left) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::D) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Right)) &&
            transforms[_id].has_value())
                _gameEngine.eventManager.getHandler<GameEngine::TransformComponent>(GameEngine::Event::PlayerMoveEvent).publish(transforms[_id].value());
    }
} // namespace RType::Client
