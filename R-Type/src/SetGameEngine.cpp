/*
** EPITECH PROJECT, 2023
** SetGameEngine.cpp
** File description:
** SetGameEngine
*/

#include "RTypeClient.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/NetworkIdComponent.hpp"#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/GravitySystem.hpp"

namespace RType::Client
{

    void RTypeClient::setGameEngineComponent()
    {
        _gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
        _gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();
        _gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
        _gameEngine.registry.registerComponent<GameEngine::CameraComponent>();
        _gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
        _gameEngine.registry.registerComponent<GameEngine::TextComponent>();
        _gameEngine.registry.registerComponent<GameEngine::PressableComponent>();
        _gameEngine.registry.registerComponent<GameEngine::NetworkIdComponent>();
    }

    void RTypeClient::setGameEngineCallback()
    {
        setConnexionCallback();
        setUpdateEntityCallback();
        setDeleteEntityCallback();
        setMovementEntityCallback();
        setShootCallback();
    }

    void RTypeClient::setGameEngineSystem()
    {
        auto drawSystem = std::make_shared<GameEngine::DrawSystem>(_gameEngine.eventManager, 800, 800);
        GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());
        GameEngine::PressableSystem pressableSystem(_gameEngine.eventManager);
        GameEngine::ControlSystem controlSystem;
        GameEngine::CollisionSystem collisionSystem;
        GameEngine::GravitySystem gravitySystem(_gameEngine.deltaTime.getDeltaTime());
        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                           SparseArray<GameEngine::ControllableComponent> &)>,
            GameEngine::TransformComponent, GameEngine::ControllableComponent>(controlSystem);
        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                           SparseArray<GameEngine::TextureComponent> &)>,
            GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);

        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> &)>,
            GameEngine::CollisionComponent>(collisionSystem);

        _gameEngine.registry.addSystem<GameEngine::PressableFunction, GameEngine::TransformComponent,
            GameEngine::TextureComponent, GameEngine::PressableComponent>(pressableSystem);

        _gameEngine.registry.addSystem<GameEngine::DrawSystem, GameEngine::TextComponent, GameEngine::TextureComponent>(
            drawSystem);
    }

    void RTypeClient::setGameEngine()
    {
        setGameEngineComponent();
        setGameEngineSystem();
        setGameEngineCallback();
    }

} // namespace RType::Client
