/*
** EPITECH PROJECT, 2023
** SetGameEngine.cpp
** File description:
** SetGameEngine
*/

#include "RTypeServer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/DamageComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/TextureComponent.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/DamageSystem.hpp"

namespace RType::Server
{

    void RTypeServer::setPrefab()
    {
        _gameEngine.prefabManager.loadPrefabFromFile("config/NonPlayerStarship.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/Dop.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/Player.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/ParallaxCollision.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/Parallax.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/PataPata.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/SimpleShoot.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/ChargedShoot.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/DestroyEntityLeft.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/DestroyEntityRight.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapUp.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapDown.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapLeft.json");
        _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapRight.json");
    }

    void RTypeServer::setGameEngineCallback()
    {
        setDestroyCallback();
    }

    void RTypeServer::setGameEngineComponent()
    {
        _gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
        _gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();
        _gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
        _gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
        _gameEngine.registry.registerComponent<GameEngine::HealthComponent>();
        _gameEngine.registry.registerComponent<GameEngine::DamageComponent>();
    }

    void RTypeServer::setGameEngineSystem()
    {
        GameEngine::CollisionSystem collisionSystem;
        GameEngine::DamageSystem damageSystem(_gameEngine.eventManager);
        GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());

        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> &)>,
            GameEngine::CollisionComponent>(collisionSystem);
        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::DamageComponent> &, SparseArray<GameEngine::HealthComponent> &)>,
            GameEngine::DamageComponent, GameEngine::HealthComponent>(damageSystem);
        _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                           SparseArray<GameEngine::TextureComponent> &)>,
            GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);
    }

    void RTypeServer::setGameEngine()
    {
        setGameEngineComponent();
        setGameEngineSystem();
        setGameEngineCallback();
        setPrefab();
    }

} // namespace RType::Server
