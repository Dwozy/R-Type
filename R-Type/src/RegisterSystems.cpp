/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RegisterSystems
*/

#include "GameManager.hpp"

void RegisterSystems(GameManager &GameManager)
{
    GameEngine::PositionSystem positionSystem(
    GameManager.gameEngine.deltaTime.getDeltaTime());
    GameEngine::ControlSystem controlSystem;
    GameEngine::DrawSystem drawSystem(GameManager.gameEngine.window);

    GameManager.gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::VelocityComponent> &,
                           SparseArray<GameEngine::ControllableComponent> &)>,
        GameEngine::VelocityComponent, GameEngine::ControllableComponent>(
        controlSystem);
    GameManager.gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::PositionComponent> &,
                           SparseArray<GameEngine::VelocityComponent> &,
                           SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::PositionComponent, GameEngine::VelocityComponent,
        GameEngine::TextureComponent>(positionSystem);
    GameManager.gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TextComponent> &,
                           SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TextComponent, GameEngine::TextureComponent>(drawSystem);
}

