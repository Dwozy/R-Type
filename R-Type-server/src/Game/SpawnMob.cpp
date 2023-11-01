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

        struct rtype::Entity newEntity = {.id = static_cast<uint16_t>(mobEntity),
            .idTexture = static_cast<uint8_t>(rtype::EntityType::MOB),
            .positionX = entityPos->position.x,
            .positionY = entityPos->position.y,
            .directionX = entityPos->velocity.x,
            .directionY = entityPos->velocity.y};
        _listIdType.insert({static_cast<uint16_t>(mobEntity), static_cast<uint8_t>(rtype::EntityType::MOB)});

        std::map<RType::Protocol::ComponentType, std::vector<bool>> componentInfo;
        componentInfo.insert({RType::Protocol::ComponentType::TRANSFORM, {true}});
        componentInfo.insert({RType::Protocol::ComponentType::COLLISION, {true}});
        auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[mobEntity];
        if (texture) {
            std::vector<bool> distribTexture(texture->textureRects.size(), true);
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, distribTexture});
        } else
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, {false}});

        for (auto &listInfo : _listInfosComponent)
            listInfo.second.insert({mobEntity, componentInfo});
        broadcastEntityInformation(mobEntity);
        // _udpServer.sendInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
    }
} // namespace RType::Server
