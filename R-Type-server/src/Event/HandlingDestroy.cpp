/*
** EPITECH PROJECT, 2023
** HandlingDestroy.cpp
** File description:
** HandlingDestroy
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::sendDestroyInfo(struct RType::Protocol::EntityIdData entity)
    {
        struct RType::Protocol::EntityIdData entityId = {.id = entity.id};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::EntityIdData>(entityId, sizeof(entityId));
        for (auto client : _udpServer.getListClients()) {
            _listInfosComponent[client.first].erase(static_cast<uint16_t>(entity.id));
            _udpServer.sendInformation(
                static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY), dataToSend, client.second);
        }
    }

    void RTypeServer::handleDestroy(struct RType::Event event)
    {
        struct RType::Protocol::EntityIdData entity = std::any_cast<struct RType::Protocol::EntityIdData>(event.data);

        try {
            GameEngine::Entity getEntity = _gameEngine.registry.getEntityById(entity.id);
            if (_listIdType.at(entity.id) == static_cast<uint8_t>(RType::TextureType::PLAYER)) {
                _nbPlayers--;
                _nbPlayers = (_nbPlayers == 0) ? -1 : _nbPlayers;
                if (!std::binary_search(_nbPlayerTexture.begin(), _nbPlayerTexture.end(), _listIndexTexture[entity.id]))
                    _nbPlayerTexture.push_back(_listIndexTexture[entity.id]);
                std::sort(_nbPlayerTexture.begin(), _nbPlayerTexture.end());
                _listIndexTexture.erase(entity.id);
                _udpServer.getListClients().erase(event.port);
            }
            if (_killEnemy && (_listIdType.at(entity.id) == static_cast<uint8_t>(RType::TextureType::SIMPLE_MOB) ||
                                  _listIdType.at(entity.id) == static_cast<uint8_t>(RType::TextureType::MEDIUM_MOB))) {
                _points += (_listIdType.at(entity.id) == static_cast<uint8_t>(RType::TextureType::MEDIUM_MOB)) ? 25 : 1;
                for (auto client : _udpServer.getListClients())
                    sendScore(client.first);
            }
            _listLifePoints.erase(static_cast<uint16_t>(entity.id));
            _listIdType.erase(static_cast<uint16_t>(entity.id));
            _timerLifePoint.erase(static_cast<uint16_t>(entity.id));
            _killEnemy = false;
            _gameEngine.registry.killEntity(getEntity);
            sendDestroyInfo(entity);
        } catch (const std::exception &e) {
            return;
        }
    }

    void RTypeServer::handleDestroyCallback(std::size_t &id)
    {
        struct RType::Protocol::EntityIdData entityId = {.id = static_cast<uint16_t>(id)};
        struct RType::Event destroyEvent = {
            .packetType = static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY), .data = entityId};
        _killEnemy = true;
        handleDestroy(destroyEvent);
    }

    void RTypeServer::setDestroyCallback()
    {
        auto &refHandlerInput = _gameEngine.eventManager.addHandler<std::size_t &>(
            static_cast<GameEngine::EventType>(GameEngine::Event::GetDestroy));
        auto handleInput = std::bind(&RType::Server::RTypeServer::handleDestroyCallback, this, std::placeholders::_1);
        refHandlerInput.subscribe(handleInput);
    }

} // namespace RType::Server
