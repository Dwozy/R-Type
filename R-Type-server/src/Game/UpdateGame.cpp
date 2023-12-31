/*
** EPITECH PROJECT, 2023
** UpdateGame.cpp
** File description:
** UpdateGame
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::sendScore(unsigned short port)
    {
        struct RType::Protocol::ScoreData score = {.score = static_cast<uint16_t>(_points)};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::ScoreData>(score, sizeof(score));

        _udpServer.sendInformation(
            static_cast<uint8_t>(RType::Protocol::PacketType::SCORE), dataToSend, _udpServer.getListClients()[port]);
    }

    void RTypeServer::updateComponentInformation(GameEngine::Entity &entity, RType::TextureType entityType)
    {
        std::map<RType::Protocol::ComponentType, std::vector<bool>> componentInfo;
        auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entity];
        RType::Protocol::ComponentType transformType = RType::Protocol::ComponentType::TRANSFORM;
        RType::Protocol::ComponentType collisionType = RType::Protocol::ComponentType::COLLISION;
        RType::Protocol::ComponentType textureType = RType::Protocol::ComponentType::TEXTURE;

        componentInfo[transformType] = {true};
        componentInfo[collisionType] = {true};
        if (texture) {
            std::vector<bool> distribTexture(texture.value().textureRects.size(), true);
            componentInfo[textureType] = distribTexture;
        } else
            componentInfo[textureType] = {false};

        for (auto &listInfo : _listInfosComponent)
            listInfo.second.insert({entity, componentInfo});
        _listIdType.insert({static_cast<uint16_t>(entity), static_cast<uint8_t>(entityType)});
    }

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

    componentList RType::Server::RTypeServer::setEntitiesComponent()
    {
        componentList infos;

        auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
        auto textures = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();
        RType::Protocol::ComponentType transformType = RType::Protocol::ComponentType::TRANSFORM;
        RType::Protocol::ComponentType collisionType = RType::Protocol::ComponentType::COLLISION;
        RType::Protocol::ComponentType textureType = RType::Protocol::ComponentType::TEXTURE;
        for (std::size_t i = 0; i < transforms.size(); i++) {
            std::map<RType::Protocol::ComponentType, std::vector<bool>> componentInfo;
            componentInfo[transformType] = {true};
            componentInfo[collisionType] = {true};
            auto texture = textures[i];
            auto transform = transforms[i];
            if (!texture && !transform)
                continue;
            if (texture) {
                std::vector<bool> distribTexture(texture->textureRects.size(), true);
                componentInfo[textureType] = distribTexture;
            } else
                componentInfo[textureType] = {false};
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(i);
            infos.insert({entity, componentInfo});
        }
        return infos;
    }

    void RTypeServer::broadcastInformation()
    {
        broadcastTransformComponent();
        broadcastTextureComponent();
        broadcastCollisionComponent();
    }

} // namespace RType::Server
