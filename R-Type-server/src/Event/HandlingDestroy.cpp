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
            _listLifePoints.erase(static_cast<uint16_t>(entity.id));
            _listIdType.erase(static_cast<uint16_t>(entity.id));
            struct RType::Protocol::EntityIdData entityId = {.id = entity.id};
            std::vector<std::byte> dataToSend =
                Serialization::serializeData<struct RType::Protocol::EntityIdData>(entityId, sizeof(entityId));
            for (auto client : _udpServer.getListClients()) {
                _listInfosComponent[client.first].erase(static_cast<uint16_t>(entity.id));
                _udpServer.sendInformation(static_cast<uint8_t>(RType::PacketType::DESTROY), dataToSend, client.second);
            }
        } catch (const std::exception &e) {
            return;
        }
    }
} // namespace RType::Server
