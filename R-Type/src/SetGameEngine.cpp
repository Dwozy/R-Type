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
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"

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
    }

    void RTypeClient::setGameEngineCallback()
    {
        setConnexionCallback();
        setUpdateEntityCallback();
        setDeleteEntityCallback();
        setMovementEntityCallback();
    }

    void RTypeClient::setGameEngineSystem()
    {
        GameEngine::DrawSystem drawSystem(_gameEngine.eventManager);
        GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());
        GameEngine::PressableSystem pressableSystem(_gameEngine.eventManager);
        GameEngine::ControlSystem controlSystem;
        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                           SparseArray<GameEngine::ControllableComponent> &)>,
            GameEngine::TransformComponent, GameEngine::ControllableComponent>(controlSystem);

        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                           SparseArray<GameEngine::TextureComponent> &)>,
            GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);

        _gameEngine.registry.addSystem<GameEngine::PressableFunction, GameEngine::TransformComponent,
            GameEngine::TextureComponent, GameEngine::PressableComponent>(pressableSystem);

        _gameEngine.registry.addSystem<
            std::function<void(SparseArray<GameEngine::TextComponent> &, SparseArray<GameEngine::TextureComponent> &)>,
            GameEngine::TextComponent, GameEngine::TextureComponent>(drawSystem);

        GameEngine::Entity camera = _gameEngine.registry.spawnEntity();
        GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 200.0f, 200.0f)}};
        auto &refCamera = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

        if (refCamera)
            _gameEngine.eventManager.publish<GameEngine::View &>(GameEngine::Event::WindowSetView, refCamera.value().view);
    }

    void RTypeClient::setGameEngine()
    {
        setGameEngineSystem();
        setGameEngineComponent();
        setGameEngineCallback();
    }

} // namespace RType::Client
