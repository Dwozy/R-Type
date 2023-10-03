/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RegisterComponent
*/

#include "GameManager.hpp"

void RegisterComponent(GameManager &GameManager)
{
    GameManager.gameEngine.registry.registerComponent<GameEngine::PositionComponent>();
    GameManager.gameEngine.registry.registerComponent<GameEngine::VelocityComponent>();
    GameManager.gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
    GameManager.gameEngine.registry.registerComponent<GameEngine::CameraComponent>();
    GameManager.gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    GameManager.gameEngine.registry.registerComponent<GameEngine::TextComponent>();
}


