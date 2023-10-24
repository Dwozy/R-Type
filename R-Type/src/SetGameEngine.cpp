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
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"

void parallaxCollision(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms)
{
    auto &selfCol = collisions[entityId];
    auto &selfTsf = transforms[entityId];

    if (!selfCol || !selfTsf)
        return;
    for (std::size_t i = 0; i < collisions.size(); i++) {
        if (i == entityId)
            continue;
        auto &col = collisions[i];
        auto &tsf = transforms[i];

        if (!col || !tsf || !col.value().isActive || col.value().layer != 10)
            continue;
        if (selfCol.value().collider.isColliding(selfTsf.value().position, col.value().collider, tsf.value().position))
            tsf.value().position.x = 199;
    }
}

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
    }

    void RTypeClient::setGameEngineSystem()
    {
        auto drawSystem = std::make_shared<GameEngine::DrawSystem>(_gameEngine.eventManager, 800, 800);
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

        _gameEngine.registry.addSystem<GameEngine::DrawSystem, GameEngine::TextComponent, GameEngine::TextureComponent>(
            drawSystem);
    }

    void RTypeClient::setGameEngine()
    {
        setGameEngineComponent();
        setGameEngineSystem();
        setGameEngineCallback();

        GameEngine::Entity camera = _gameEngine.registry.spawnEntity();
        GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 200.0f, 200.0f)}};
        auto &refCamera = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

        if (refCamera)
            _gameEngine.eventManager.publish<GameEngine::View &>(
                GameEngine::Event::WindowSetView, refCamera.value().view);

        GameEngine::Entity parallax1 = _gameEngine.registry.spawnEntity();
        _gameEngine.registry.addComponent<GameEngine::TransformComponent>(parallax1,
            GameEngine::TransformComponent{GameEngine::Vector2<float>(0.0, 0.0), GameEngine::Vector2<float>(-50, 0.0)});
        GameEngine::Rectf collider(199, 0, 30, 200);
        GameEngine::CollisionComponent col = {.collider = collider, .layer = 10};
        _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(parallax1, col);

        auto &parallax1Tex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(parallax1,
            GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), false, {}, 0, true, 0, 0, 0});
        parallax1Tex.value().texture.load("R-Type/assets/parallax.png", GameEngine::Rect<int>(0, 0, 1080, 1080));
        parallax1Tex.value().sprite.load(parallax1Tex.value().texture);
        parallax1Tex.value().sprite.setScale(0.1851, 0.1851);

        GameEngine::Entity parallax2 = _gameEngine.registry.spawnEntity();
        _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
            parallax2, GameEngine::TransformComponent{
                           GameEngine::Vector2<float>(199.0, 0.0), GameEngine::Vector2<float>(-50, 0.0)});
        auto &col2 = _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(
            parallax2, GameEngine::CollisionComponent{.collider = collider, .layer = 10});

        auto &parallax2Tex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(parallax2,
            GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), false, {}, 0, true, 0, 0, 0});
        parallax2Tex.value().texture.load("R-Type/assets/parallax.png", GameEngine::Rect<int>(0, 0, 1080, 1080));
        parallax2Tex.value().sprite.load(parallax2Tex.value().texture);
        parallax2Tex.value().sprite.setScale(0.1851, 0.1851);

        GameEngine::Entity parallaxRange = _gameEngine.registry.spawnEntity();
        _gameEngine.registry.addComponent<GameEngine::TransformComponent>(parallaxRange,
            GameEngine::TransformComponent{GameEngine::Vector2<float>(-20.0, 0), GameEngine::Vector2<float>(0.0, 0.0)});
        auto &parRange = _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(
            parallaxRange, GameEngine::CollisionComponent{.collider = GameEngine::Rectf(0, 0, 20, 200), .layer = 11});
        parRange.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                _gameEngine.registry, parallaxCollision);
    }

} // namespace RType::Client
