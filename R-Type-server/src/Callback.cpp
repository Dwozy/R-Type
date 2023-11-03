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
            if (selfCol.value().layer != 3 && selfCol.value().layer != 5 && selfCol.value().layer != 6 &&
                selfCol.value().layer != 7)
                continue;
            if (selfCol.value().layer == 5 && col.value().layer != 6)
                continue;
            if (selfCol.value().layer == 7 && col.value().layer != 6)
                continue;
            if (selfCol.value().layer == 6 && col.value().layer != 5)
                continue;
            if (selfCol.value().collider.isColliding(
                    selfTsf.value().position, col.value().collider, tsf.value().position)) {
                if (col.value().layer == 6 && (selfCol.value().layer == 5 || selfCol.value().layer == 7)) {
                    std::cout << "Win point : " << _points << std::endl;
                    _points++;
                }
                struct RType::Protocol::EntityIdData entityId = {.id = static_cast<uint16_t>(i)};
                struct RType::Event destroyEvent = {
                    .packetType = static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY), .data = entityId};
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

    void RTypeServer::handlingLifePoint(std::size_t entityId)
    {
        if (_listLifePoints.find(static_cast<uint16_t>(entityId)) == _listLifePoints.end())
            return;
        if (_timerLifePoint.find(static_cast<uint16_t>(entityId)) == _timerLifePoint.end())
            return;
        if (!_timerLifePoint.at(static_cast<uint16_t>(entityId)).first)
            return;
        if (_listLifePoints.at(static_cast<uint16_t>(entityId)) == 0) {
            _nbPlayers--;
            if (_nbPlayers == 0)
                _nbPlayers = -1;
            struct RType::Protocol::EntityIdData entityValue = {.id = static_cast<uint16_t>(entityId)};
            struct RType::Event destroyEvent = {
                .packetType = static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY), .data = entityValue};
            _eventQueue.push(destroyEvent);
        } else {
            _listLifePoints.at(static_cast<uint16_t>(entityId))--;
            _timerLifePoint.at(static_cast<uint16_t>(entityId)).first = false;
            _timerLifePoint.at(static_cast<uint16_t>(entityId)).second = std::chrono::steady_clock::now();
            struct RType::Protocol::StatePlayerData statePlayer = {
                .id = static_cast<uint8_t>(entityId), .invincibility = static_cast<uint8_t>(true)};
            std::vector<std::byte> dataToSend =
                Serialization::serializeData<struct RType::Protocol::StatePlayerData>(statePlayer, sizeof(statePlayer));
            for (auto client : _udpServer.getListClients())
                _udpServer.sendInformation(
                    static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_STATE), dataToSend, client.second);
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
                handlingLifePoint(entityId);
            }
        }
    }

} // namespace RType::Server
