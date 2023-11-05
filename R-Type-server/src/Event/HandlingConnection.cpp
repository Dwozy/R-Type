/*
** EPITECH PROJECT, 2023
** HandlingConnection.cpp
** File description:
** HandlingConnexion
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::sendControllableInformation(GameEngine::Entity &entity, unsigned short port)
    {
        struct RType::Protocol::ControllableData player = {
            .id = static_cast<uint16_t>(entity),
        };
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::ControllableData>(player, sizeof(player));
        _udpServer.sendInformation(static_cast<uint8_t>(RType::Protocol::ComponentType::CONTROLLABLE), dataToSend,
            _udpServer.getListClients()[port]);
    }

    void RTypeServer::handleConnexion(struct RType::Event event)
    {
        GameEngine::Entity entity =
            _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry, false);
        auto &entityPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[entity];
        auto &entityCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[entity];
        auto &entityTexture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entity];

        _nbPlayers++;
        if (!_nbPlayerTexture.empty()) {
            entityTexture.value().textureRects[0].top += ((_nbPlayerTexture.front() - 1) % 5) * 17;
            _listIndexTexture.insert({static_cast<uint16_t>(entity), _nbPlayerTexture.front()});
            _nbPlayerTexture.erase(_nbPlayerTexture.begin());
        } else {
            entityTexture.value().textureRects[0].top += ((_nbPlayers - 1) % 5) * 17;
            _listIndexTexture.insert({static_cast<uint16_t>(entity), _nbPlayers});
        }
        entityPos.value().position = GameEngine::Vector2<float>(25, 25);
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

        _listInfosComponent.insert({event.port, setEntitiesComponent()});
        _listLifePoints.insert({static_cast<uint16_t>(entity), 5});
        _timerLifePoint.insert({static_cast<uint16_t>(entity), {true, std::chrono::steady_clock::now()}});
        updateComponentInformation(entity, RType::TextureType::PLAYER);
        broadcastEntityInformation(entity);
        sendControllableInformation(entity, event.port);
        sendScore(event.port);
    }

} // namespace RType::Server
