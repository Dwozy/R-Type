/*
** EPITECH PROJECT, 2023
** HandlingCollision.cpp
** File description:
** HandlingCollision
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::handleCollisionResponse(struct rtype::Event event)
    {
        struct RType::Protocol::CollisionResponse response =
            std::any_cast<struct RType::Protocol::CollisionResponse>(event.data);

        if (_listInfosComponent.find(event.port) == _listInfosComponent.end())
            return;
        if (_listInfosComponent[event.port].find(response.id) == _listInfosComponent[event.port].end())
            return;
        _listInfosComponent.at(event.port).at(response.id).at(RType::Protocol::ComponentType::COLLISION).front() = false;
    }

    void RTypeServer::sendCollisionComponent(uint16_t id, GameEngine::Rectf collider, std::size_t layer, asio::ip::udp::endpoint &endpoint)
    {
        struct RType::Protocol::CollisionData collisionData = {.id = id,
            .idCallback = static_cast<uint8_t>(_listIdType.at(id)),
            .rectLeft = collider.left,
            .rectTop = collider.top,
            .rectWidth = collider.width,
            .rectHeight = collider.height,
            .layer = static_cast<uint8_t>(layer)};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::CollisionData>(collisionData, sizeof(collisionData));
        _udpServer.sendInformation(static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION), dataToSend, endpoint);
    }

    void RTypeServer::broadcastCollisionComponent()
    {
        auto &collisions = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>();

        for (std::size_t i = 0; i < collisions.size(); i++) {
            auto collision = collisions[i];
            if (!collision)
                continue;
            for (auto client : _udpServer.getListClients()) {
                if (_listInfosComponent[client.first].find(i) != _listInfosComponent[client.first].end() &&
                    _listInfosComponent[client.first].at(i).at(RType::Protocol::ComponentType::COLLISION).front()) {
                    sendCollisionComponent(
                        static_cast<uint16_t>(i), collision.value().collider, collision.value().layer, client.second);
                }
            }
        }
    }
} // namespace RType::Server
