/*
** EPITECH PROJECT, 2023
** SpawnMob.cpp
** File description:
** SpawnMob
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::spawnMob()
    {
        GameEngine::Entity mobEntity =
            _gameEngine.prefabManager.createEntityFromPrefab("patapata", _gameEngine.registry, false);
        auto &entityPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[mobEntity];
        float randPosY = (rand() % 180) + 10;
        entityPos->position = GameEngine::Vector2<float>(200, randPosY);
        auto &entityCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[mobEntity];
        auto destroyMobCallback = std::bind(&RType::Server::RTypeServer::destroyEntityCallback, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        entityCollider.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                _gameEngine.registry, destroyMobCallback);

        updateComponentInformation(mobEntity, RType::TextureType::MOB);
        broadcastEntityInformation(mobEntity);
    }
} // namespace RType::Server
