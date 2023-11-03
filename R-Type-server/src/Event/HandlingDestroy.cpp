/*
** EPITECH PROJECT, 2023
** HandlingDestroy.cpp
** File description:
** HandlingDestroy
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::handleDestroy(struct RType::Event event)
    {
        struct RType::Protocol::EntityIdData entity = std::any_cast<struct RType::Protocol::EntityIdData>(event.data);

        try {
            GameEngine::Entity getEntity = _gameEngine.registry.getEntityById(entity.id);
            if (_listIdType[entity.id] == static_cast<uint8_t>(RType::TextureType::PLAYER))
                pos--;
            _gameEngine.registry.killEntity(getEntity);
            if (_listIdType.at(entity.id) == static_cast<uint8_t>(RType::TextureType::PLAYER)) {
                _nbPlayers--;
                _nbPlayers = (_nbPlayers == 0) ? -1 : _nbPlayers;
            }
            if (_listIdType.at(entity.id) == static_cast<uint8_t>(RType::TextureType::SIMPLE_MOB))
                _points++;
            if (_listIdType.at(entity.id) == static_cast<uint8_t>(RType::TextureType::SIMPLE_MOB))
                _points += 25;
            _listLifePoints.erase(static_cast<uint16_t>(entity.id));
            _listIdType.erase(static_cast<uint16_t>(entity.id));
            _timerLifePoint.erase(static_cast<uint16_t>(entity.id));
            struct RType::Protocol::EntityIdData entityId = {.id = entity.id};
            std::vector<std::byte> dataToSend =
                Serialization::serializeData<struct RType::Protocol::EntityIdData>(entityId, sizeof(entityId));
            for (auto client : _udpServer.getListClients()) {
                _listInfosComponent[client.first].erase(static_cast<uint16_t>(entity.id));
                _udpServer.sendInformation(
                    static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY), dataToSend, client.second);
            }
        } catch (const std::exception &e) {
            return;
        }
    }

    void RTypeServer::handleDestroyCallback(std::size_t &id)
    {
        struct RType::Protocol::EntityIdData entityId = {.id = static_cast<uint16_t>(id)};
        struct RType::Event destroyEvent = {
            .packetType = static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY), .data = entityId};
        _eventQueue.push(destroyEvent);
    }

    void RTypeServer::setDestroyCallback()
    {
        auto &refHandlerInput = _gameEngine.eventManager.addHandler<std::size_t &>(
            static_cast<GameEngine::EventType>(GameEngine::Event::GetDestroy));
        auto handleInput = std::bind(&RType::Server::RTypeServer::handleDestroyCallback, this, std::placeholders::_1);
        refHandlerInput.subscribe(handleInput);
    }

} // namespace RType::Server
