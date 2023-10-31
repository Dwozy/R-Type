/*
** EPITECH PROJECT, 2023
** HandleEvent.cpp
** File description:
** HandleEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::handleNewEntity(struct rtype::Event event)
    {
        struct rtype::Entity entity = std::any_cast<struct rtype::Entity>(event.data);
        _gameEngine.eventManager.getHandler<struct rtype::Entity>(GameEngine::Event::GetNewEntity).publish(entity);
    }

    void RTypeClient::handleDisconnexion(struct rtype::Event event)
    {
        struct rtype::EntityId entity = std::any_cast<struct rtype::EntityId>(event.data);
        _gameEngine.eventManager.getHandler<struct rtype::EntityId>(GameEngine::Event::DeleteEntity).publish(entity);
    }

    void RTypeClient::handleEntity(struct rtype::Event event)
    {
        struct rtype::Entity entity = std::any_cast<struct rtype::Entity>(event.data);
        _gameEngine.eventManager.getHandler<struct rtype::Entity>(GameEngine::Event::GetEntity).publish(entity);
    }

    void RTypeClient::handleEvent()
    {
        struct rtype::Event event;

        while (_eventQueue.size() != 0) {
            event = _eventQueue.pop();
            switch (event.packetType) {
            case static_cast<uint8_t>(rtype::PacketType::ENTITY):
                handleEntity(event);
                break;
            case static_cast<uint8_t>(rtype::PacketType::CONNECTED):
                handleNewEntity(event);
                break;
            case static_cast<uint8_t>(rtype::PacketType::DESTROY):
                handleDisconnexion(event);
                break;
                // case static_cast<uint8_t>(rtype::PacketType::SHOOT):
                //     handleShoot(event);
                //     break;
            }
        }
    }
} // namespace RType::Client
