/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ShootEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::getCollisionInformation(struct RType::Protocol::CollisionData collisionData)
    {
        auto &collisions = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>();
        std::size_t id = 0;

        if (!_searchEntity(collisionData.id)) {
            GameEngine::Entity entity = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                entity, GameEngine::NetworkIdComponent{collisionData.id});
            GameEngine::Rectf rect(
                collisionData.rectLeft, collisionData.rectTop, collisionData.rectWidth, collisionData.rectHeight);
            GameEngine::CollisionComponent col = {.collider = rect, .layer = collisionData.layer};
            _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(entity, col);
            auto &entityCollider = _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(entity, col);
            if (collisionData.idCallback == static_cast<uint8_t>(RType::TextureType::PLAYER)) {
                auto colliderCallback = std::bind(&RType::Client::RTypeClient::playerCollisionCallback, this,
                    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                entityCollider.value()
                    .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                                   SparseArray<GameEngine::TransformComponent> &)>,
                        GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                        _gameEngine.registry, colliderCallback);
            }
        }
        id = _findEntity(collisionData.id);
        if (!collisions[id]) {
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
            GameEngine::Rectf rect(
                collisionData.rectLeft, collisionData.rectTop, collisionData.rectWidth, collisionData.rectHeight);
            GameEngine::CollisionComponent col = {.collider = rect, .layer = collisionData.layer};
            auto &entityCollider = _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(entity, col);
            if (collisionData.idCallback == static_cast<uint8_t>(RType::TextureType::PLAYER)) {
                auto colliderCallback = std::bind(&RType::Client::RTypeClient::playerCollisionCallback, this,
                    std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                entityCollider.value()
                    .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                                   SparseArray<GameEngine::TransformComponent> &)>,
                        GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                        _gameEngine.registry, colliderCallback);
            }
        } else {
            struct RType::Protocol::CollisionResponse response = {.id = collisionData.id};
            std::vector<std::byte> dataToSend =
                Serialization::serializeData<struct RType::Protocol::CollisionResponse>(response, sizeof(response));
            _udpClient.sendDataInformation(
                dataToSend, static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION_RES));
        }
    }

    void RTypeClient::setCollisionCallback()
    {
        auto &refHandleCollision = _gameEngine.eventManager.addHandler<struct RType::Protocol::CollisionData>(
            static_cast<GameEngine::EventType>(GameEngine::Event::GetCollision));
        auto handleGetCollision =
            std::bind(&RType::Client::RTypeClient::getCollisionInformation, this, std::placeholders::_1);
        refHandleCollision.subscribe(handleGetCollision);
    }
} // namespace RType::Client
