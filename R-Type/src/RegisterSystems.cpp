/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RegisterSystems
*/

#include "Game.hpp"

void RegisterSystems(GameEngine::GameEngine &GameEngine)
{
    GameEngine::PositionSystem positionSystem(GameEngine.deltaTime.getDeltaTime());
    GameEngine::ControlSystem controlSystem;
    GameEngine::DrawSystem drawSystem(GameEngine.window);
    GameEngine::AnimeSystem animeSystem;

    GameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::VelocityComponent> &,
                           SparseArray<GameEngine::ControllableComponent> &)>,
        GameEngine::VelocityComponent, GameEngine::ControllableComponent>(
        controlSystem);
    GameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::PositionComponent> &,
                           SparseArray<GameEngine::VelocityComponent> &,
                           SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::PositionComponent, GameEngine::VelocityComponent,
        GameEngine::TextureComponent>(positionSystem);
    GameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TextComponent> &,
                           SparseArray<GameEngine::TextureComponent> &,
                           SparseArray<GameEngine::TextureAnimatedComponent> &)>,
        GameEngine::TextComponent, GameEngine::TextureComponent, GameEngine::TextureAnimatedComponent>(drawSystem);
    GameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TextureAnimatedComponent> &)>, GameEngine::TextureAnimatedComponent>(animeSystem);
}

