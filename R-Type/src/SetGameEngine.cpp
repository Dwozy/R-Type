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
#include "components/NetworkIdComponent.hpp"
#include "components/InputComponent.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/GravitySystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "systems/InputSystem.hpp"

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
        _gameEngine.registry.registerComponent<GameEngine::GravityComponent>();
        _gameEngine.registry.registerComponent<GameEngine::InputComponent>();
    }

    void RTypeClient::setGameEngineCallback()
    {
        setDeleteEntityCallback();
        setTransformCallback();
        setTextureCallback();
        setCollisionCallback();
        setControllableCallback();
        setInputCallback();
    }

    void RTypeClient::setGameEngineSystem()
    {
#ifdef DEBUG
        auto drawSystem =
            std::make_shared<GameEngine::DrawSystem>(_gameEngine.eventManager, _gameEngine.debugMenu, 800, 800);
#else
        auto drawSystem = std::make_shared<GameEngine::DrawSystem>(_gameEngine.eventManager, 800, 800);
#endif
        GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());
        GameEngine::PressableSystem pressableSystem(_gameEngine.eventManager);
        GameEngine::ControlSystem controlSystem;
        GameEngine::CollisionSystem collisionSystem;
        GameEngine::GravitySystem gravitySystem(_gameEngine.deltaTime.getDeltaTime());
        GameEngine::AnimationSystem animationSystem(_gameEngine.deltaTime.getDeltaTime());
        GameEngine::InputSystem inputSystem(_gameEngine.eventManager);

        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                           SparseArray<GameEngine::ControllableComponent> &)>,
            GameEngine::TransformComponent, GameEngine::ControllableComponent>(controlSystem);

        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                           SparseArray<GameEngine::TextureComponent> &, SparseArray<GameEngine::GravityComponent> &)>,
            GameEngine::TransformComponent, GameEngine::TextureComponent, GameEngine::GravityComponent>(positionSystem);

        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> &)>,
            GameEngine::CollisionComponent>(collisionSystem);

        _gameEngine.registry.addSystem<GameEngine::PressableFunction, GameEngine::TransformComponent,
            GameEngine::TextureComponent, GameEngine::PressableComponent>(pressableSystem);

        _gameEngine.registry.addSystem<GameEngine::DrawSystem, GameEngine::TextComponent, GameEngine::TextureComponent, GameEngine::CameraComponent>(
            drawSystem);

        _gameEngine.registry
            .addSystem<std::function<void(SparseArray<GameEngine::TextureComponent> &)>, GameEngine::TextureComponent>(
                animationSystem);

        _gameEngine.registry
            .addSystem<std::function<void(SparseArray<GameEngine::InputComponent> &)>, GameEngine::InputComponent>(
                inputSystem);
    }

    void RTypeClient::setGameEngine()
    {
        setGameEngineComponent();
        setGameEngineSystem();
        setGameEngineCallback();
    }

} // namespace RType::Client
