/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RegisterSystems
*/

#include "GameManager.hpp"

void RegisterSystems(GameManager &GameManager)
{
    GameManager.gameEngine.registry.addSystem<std::function<void(GameEngine::GameEngine &, SparseArray<GameEngine::VelocityComponent> &, SparseArray<GameEngine::ControllableComponent> &)>, GameEngine::VelocityComponent, GameEngine::ControllableComponent>(GameEngine::controlSystem, GameManager.gameEngine);
    GameManager.gameEngine.registry.addSystem<std::function<void(GameEngine::GameEngine &, SparseArray<GameEngine::PositionComponent> &, SparseArray<GameEngine::VelocityComponent> &, SparseArray<GameEngine::TextureComponent> &)>, GameEngine::PositionComponent, GameEngine::VelocityComponent, GameEngine::TextureComponent>(GameEngine::positionSystem, GameManager.gameEngine);
    GameManager.gameEngine.registry.addSystem<std::function<void(GameEngine::GameEngine &, SparseArray<GameEngine::TextComponent> &, SparseArray<GameEngine::TextureComponent> &)>, GameEngine::TextComponent, GameEngine::TextureComponent>(GameEngine::drawSystem, GameManager.gameEngine);
}

