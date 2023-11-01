/*
** EPITECH PROJECT, 2023
** HandlingConnection.cpp
** File description:
** HandlingConnexion
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::handleConnexion(struct rtype::Event event)
    {
        GameEngine::Entity entity =
            _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry, false);
        auto &entityPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[entity];
        entityPos.value().position = GameEngine::Vector2<float>(pos * 25, pos * 25);
        auto &entityCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[entity];

        auto colliderCallback = std::bind(&RType::Server::RTypeServer::playerCollisionCallback, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        entityCollider.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, colliderCallback);

        auto colliderDamageCollider = std::bind(&RType::Server::RTypeServer::playerDamageCallback, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        entityCollider.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                _gameEngine.registry, colliderDamageCollider);

        pos++;
        _nbPlayers++;
        _listInfosComponent.insert({event.port, setEntitiesComponent()});

        std::map<RType::Protocol::ComponentType, std::vector<bool>> componentInfo;
        componentInfo.insert({RType::Protocol::ComponentType::TRANSFORM, {true}});
        componentInfo.insert({RType::Protocol::ComponentType::COLLISION, {true}});

        auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent> () [entity];
        if (texture) {
            std::vector<bool> distribTexture(texture.value().textureRects.size(), true);
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, distribTexture});
        } else
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, {false}});

        for (auto &listInfo : _listInfosComponent)
            listInfo.second.insert({entity, componentInfo});

        _listLifePoints.insert({static_cast<uint16_t>(entity), 5});
        _listIdType.insert({static_cast<uint16_t>(entity), static_cast<uint8_t>(rtype::EntityType::PLAYER)});
        broadcastEntityInformation(entity);

        struct RType::Protocol::ControllableData player = {.id = static_cast<uint8_t> (entity)};
        std::vector<std::byte> dataToSend = Serialization::serializeData<struct RType::Protocol::ControllableData> (player, sizeof(player));
        _udpServer.sendInformation(static_cast<uint8_t> (RType::Protocol::ComponentType::CONTROLLABLE), dataToSend, _udpServer.getListClients()[event.port]);
    }

} // namespace RType::Server
