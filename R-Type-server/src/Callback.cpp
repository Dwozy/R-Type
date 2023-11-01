/*
** EPITECH PROJECT, 2023
** Callback.cpp
** File description:
** Callback
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::destroyEntityCallback(const std::size_t &entityId,
        SparseArray<GameEngine::CollisionComponent> &collisions,
        SparseArray<GameEngine::TransformComponent> &transforms)
    {
        auto &selfCol = collisions[entityId];
        auto &selfTsf = transforms[entityId];

        if (!selfCol || !selfTsf)
            return;
        for (std::size_t i = 0; i < collisions.size(); i++) {
            if (i == entityId)
                continue;
            auto &col = collisions[i];
            auto &tsf = transforms[i];
            if (!col || !tsf || !col.value().isActive)
                continue;
            if (selfCol.value().layer != 3 && selfCol.value().layer != 5 && selfCol.value().layer != 6)
                continue;
            if (selfCol.value().layer == 5 && col.value().layer != 6)
                continue;
            if (selfCol.value().layer == 6 && col.value().layer != 5)
                continue;

            if (selfCol.value().collider.isColliding(
                    selfTsf.value().position, col.value().collider, tsf.value().position)) {
                struct RType::Protocol::EntityIdData entityId = {.id = static_cast<uint16_t>(i)};
                struct rtype::Event destroyEvent = {
                    .packetType = static_cast<uint8_t>(rtype::PacketType::DESTROY), .data = entityId};
                _eventQueue.push(destroyEvent);
            }
        }
    }

    void RTypeServer::playerCollisionCallback(const std::size_t &entityId,
        SparseArray<GameEngine::CollisionComponent> &collisions,
        SparseArray<GameEngine::TransformComponent> &transforms)
    {
        auto &selfCol = collisions[entityId];
        auto &selfTsf = transforms[entityId];

        if (!selfCol || !selfTsf)
            return;
        for (std::size_t i = 0; i < collisions.size(); i++) {
            if (i == entityId)
                continue;
            auto &col = collisions[i];
            auto &tsf = transforms[i];

            if (!col || !tsf || !col.value().isActive || col.value().layer != 2)
                continue;
            selfCol.value().collider.handleCollisionFromRect(
                selfTsf.value().position, col.value().collider, tsf.value().position);
        }
    }

    void RTypeServer::playerDamageCallback(const std::size_t &entityId,
        SparseArray<GameEngine::CollisionComponent> &collisions,
        SparseArray<GameEngine::TransformComponent> &transforms)
    {
        auto &selfCol = collisions[entityId];
        auto &selfTsf = transforms[entityId];

        if (!selfCol || !selfTsf)
            return;
        for (std::size_t i = 0; i < collisions.size(); i++) {
            if (i == entityId)
                continue;
            auto &col = collisions[i];
            auto &tsf = transforms[i];

            if (!col || !tsf || !col.value().isActive || col.value().layer != 6)
                continue;
            if (selfCol.value().collider.isColliding(
                    selfTsf.value().position, col.value().collider, tsf.value().position)) {
                if (_listLifePoints.find(static_cast<uint16_t>(entityId)) != _listLifePoints.end()) {
                    if (_listLifePoints.at(static_cast<uint16_t>(entityId)) == 0) {
                        _nbPlayers--;
                        if (_nbPlayers == 0)
                            _nbPlayers = -1;
                        struct RType::Protocol::EntityIdData entityValue = {.id = static_cast<uint16_t>(entityId)};
                        struct rtype::Event destroyEvent = {
                            .packetType = static_cast<uint8_t>(rtype::PacketType::DESTROY), .data = entityValue};
                        _eventQueue.push(destroyEvent);
                    } else
                        _listLifePoints.at(static_cast<uint16_t>(entityId))--;
                }
            }
        }
    }

} // namespace RType::Server
