/*
** EPITECH PROJECT, 2023
** UpdateGame.cpp
** File description:
** UpdateGame
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::broadcastEntityInformation(const GameEngine::Entity &entity)
    {
        auto transform = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[entity];
        auto collision = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[entity];
        auto texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entity];

        if (!transform)
            return;
        for (auto client : _udpServer.getListClients()) {
            if (_listInfosComponent.find(client.first) == _listInfosComponent.end())
                continue;
            if (_listInfosComponent[client.first].find(entity) == _listInfosComponent[client.first].end())
                continue;
            sendTransformComponent(
                static_cast<uint16_t>(entity), transform->position, transform->velocity, client.second);
            if (_listInfosComponent[client.first].at(entity).at(RType::Protocol::ComponentType::COLLISION).front())
                sendCollisionComponent(
                    static_cast<uint16_t>(entity), collision->collider, collision->layer, client.second);
            std::size_t size =
                _listInfosComponent[client.first][entity][RType::Protocol::ComponentType::TEXTURE].size();
            checkSendingTexture(_listInfosComponent[client.first][entity][RType::Protocol::ComponentType::TEXTURE],
                entity, client.second);
        }
    }

    void RTypeServer::broadcastInformation()
    {
        broadcastTransformComponent();
        broadcastTextureComponent();
        broadcastCollisionComponent();
    }

} // namespace RType::Server
