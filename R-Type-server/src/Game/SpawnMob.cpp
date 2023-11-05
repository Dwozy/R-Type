/*
** EPITECH PROJECT, 2023
** SpawnMob.cpp
** File description:
** SpawnMob
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::spawnEntityMob(const std::string &mob, RType::TextureType mobType)
    {
        GameEngine::Entity mobEntity =
            _gameEngine.prefabManager.createEntityFromPrefab(mob, _gameEngine.registry, false);
        auto &entityPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[mobEntity];
        auto &entityTexture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[mobEntity];

        GameEngine::Recti rect = entityTexture.value().textureRects[0];
        float randPosY = (rand() % (200 - rect.height)) + 5;
        entityPos->position = GameEngine::Vector2<float>(200, randPosY);
        auto &entityCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[mobEntity];
        auto destroyMobCallback = std::bind(&RType::Server::RTypeServer::destroyEntityCallback, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        entityCollider.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                _gameEngine.registry, destroyMobCallback);
        updateComponentInformation(mobEntity, mobType);
        broadcastEntityInformation(mobEntity);
    }

    void RTypeServer::spawnMob(std::chrono::steady_clock::time_point &now)
    {
        std::chrono::duration<float> _deltaTimeDop =
            std::chrono::duration_cast<std::chrono::duration<float>>(now - _timers["dop"]);
        std::chrono::duration<float> _deltaTimePatapata =
            std::chrono::duration_cast<std::chrono::duration<float>>(now - _timers["patapata"]);

        if (_deltaTimeDop.count() > 8.0) {
            spawnEntityMob("dop", RType::TextureType::MEDIUM_MOB);
            _timers["dop"] = now;
        }
        if (_deltaTimePatapata.count() > 2.0) {
            spawnEntityMob("patapata", RType::TextureType::SIMPLE_MOB);
            _timers["patapata"] = now;
        }
    }
} // namespace RType::Server
