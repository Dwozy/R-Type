/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GameScene
*/

#include "scenes/GameScene.hpp"
#include "utils/CollisionsUtils.hpp"
#include <iostream>
#include <functional>

void standardGravityCollisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms, SparseArray<GameEngine::GravityComponent> &gravity)
{
    auto &selfCol = collisions[entityId];
    auto &selfTsf = transforms[entityId];
    auto &selfGrav = gravity[entityId];

    bool hasCollidedOnTop = false;

    if (!selfCol || !selfTsf || !selfGrav)
        return;
    for (std::size_t i = 0; i < collisions.size(); i++) {
        if (i == entityId)
            continue;
        auto &col = collisions[i];
        auto &tsf = transforms[i];

        if (!col || !tsf || !col.value().isActive || col.value().layer != 30)
            continue;
        auto result = GameEngine::replaceOnTop(selfTsf->position, selfCol->collider, tsf->position, col->collider);
        if (result == 1)
            hasCollidedOnTop = true;
    }
    if (hasCollidedOnTop) {
        selfGrav.value().cumulatedGVelocity = {0, 0};
        selfGrav.value().isActive = false;
    } else
        selfGrav.value().isActive = true;
}

void GameScene::load()
{
    std::cout << "Loading GameScene" << std::endl;
    if (_state == GameState::Mainmenu || _state == GameState::Restart) {
        std::cout << "create game from start" << std::endl;

        _gameEngine.prefabManager.createEntityFromPrefab("background", _gameEngine.registry);
        auto minimap_camera = _gameEngine.prefabManager.createEntityFromPrefab("minimap_camera", _gameEngine.registry);
        auto camera = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
        _id = _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry);
        std::cout << "player is " << _id << std::endl;

        auto &camComponent = _gameEngine.registry.getComponent<GameEngine::CameraComponent>()[camera];
        camComponent->target = _id;

        _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[_id]
            .value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::GravityComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent, GameEngine::GravityComponent>(
                _gameEngine.registry, standardGravityCollisionCallback);

        GameEngine::Entity block =
            _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry);

        _mapLoader.loadMap("Platformer/maps/map1", {0, _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[block]->position.y - 7 * 32}, 32);
    }
    if (_state == GameState::Pause) {
        std::cout << "resume game" << std::endl;
    }
}

void GameScene::unload() { std::cout << "unloading GameScene" << std::endl; }
