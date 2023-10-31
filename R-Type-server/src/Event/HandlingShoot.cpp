/*
** EPITECH PROJECT, 2023
** HandlingShoot.cpp
** File description:
** HandlingShoot
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::handleShoot(struct rtype::Event event)
    {
        auto shootInfo = std::any_cast<RType::Protocol::ShootData>(event.data);
        GameEngine::Entity shootEntity =
            _gameEngine.prefabManager.createEntityFromPrefab("shoot", _gameEngine.registry, false);
        GameEngine::Recti rectPlayer = {0, 0, 0, 0};

        auto &shootPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[shootEntity];
        for (auto &entityTexture : _listIdType) {
            if (entityTexture.second == static_cast<uint8_t>(rtype::EntityType::PLAYER)) {
                rectPlayer = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entityTexture.first]
                                 .value()
                                 .textureRects[0];
                break;
            }
        }
        auto &shootCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[shootEntity];
        auto destroyShootCallback = std::bind(&RTypeServer::destroyEntityCallback, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        shootCollider.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                _gameEngine.registry, destroyShootCallback);
        shootPos->position =
            GameEngine::Vector2<float>(shootInfo.x + (rectPlayer.width / 2), shootInfo.y + (rectPlayer.height / 2));

        std::map<RType::Protocol::ComponentType, std::vector<bool>> componentInfo;
        componentInfo.insert({RType::Protocol::ComponentType::TRANSFORM, {true}});
        componentInfo.insert({RType::Protocol::ComponentType::COLLISION, {true}});

        auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[shootEntity];
        if (texture) {
            std::vector<bool> distribTexture(texture.value().textureRects.size(), true);
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, distribTexture});
        } else
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, {false}});

        for (auto &listInfo : _listInfosComponent)
            listInfo.second.insert({shootEntity, componentInfo});
        _listIdType.insert({static_cast<uint16_t>(shootEntity), static_cast<uint8_t>(rtype::EntityType::SHOOT)});
        broadcastEntityInformation(shootEntity);
    }
} // namespace RType::Server
