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

void GameScene::BlockcollisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
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
        if (entityId == _id)
            _jumping = false;
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

        auto minimap_camera = _gameEngine.prefabManager.createEntityFromPrefab("minimap_camera", _gameEngine.registry);
        auto camera = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
        _entities.push_back(camera);
        _entities.push_back(minimap_camera);
        _id = _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry);
        std::cout << "player is " << _id << std::endl;

        auto &camComponent = _gameEngine.registry.getComponent<GameEngine::CameraComponent>()[camera];
        camComponent->target = _id;

        auto bolckColliderCallback = std::bind(&GameScene::BlockcollisionCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[_id]
            .value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::GravityComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent, GameEngine::GravityComponent>(
                _gameEngine.registry, bolckColliderCallback);

        GameEngine::Entity block = _gameEngine.prefabManager.createEntityFromPrefab("box", _gameEngine.registry);
        _entities.push_back(block);
        auto &blockTransform = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[block];
        blockTransform->position = {50, 50};

        GameEngine::Entity background = _gameEngine.prefabManager.createEntityFromPrefab("background", _gameEngine.registry);
        _entities.push_back(background);
        auto enemy = _gameEngine.prefabManager.createEntityFromPrefab("enemy", _gameEngine.registry);
        _entities.push_back(enemy);
        _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[enemy]
            .value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::GravityComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent, GameEngine::GravityComponent>(
                _gameEngine.registry, bolckColliderCallback);

        GameEngine::Entity block2 =
            _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry);
        _entities.push_back(enemy);
    }
    if (_state == GameState::Pause) {
        std::cout << "resume game" << std::endl;
    }
}

void GameScene::unload()
{
    for (std::size_t i = 0; i < _entities.size(); i++)
        _gameEngine.registry.killEntity(_entities[i]);
    std::cout << "unloading GameScene" << std::endl;
}
