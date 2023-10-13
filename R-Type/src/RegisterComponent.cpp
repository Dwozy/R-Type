/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RegisterComponent
*/

#include "GameEngine.hpp"

void RegisterComponent(GameEngine::GameEngine &GameEngine)
{
    GameEngine.registry.registerComponent<GameEngine::PositionComponent>();
    GameEngine.registry.registerComponent<GameEngine::VelocityComponent>();
    GameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
    GameEngine.registry.registerComponent<GameEngine::CameraComponent>();
    GameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    GameEngine.registry.registerComponent<GameEngine::TextureAnimatedComponent>();
    GameEngine.registry.registerComponent<GameEngine::TextComponent>();
}
