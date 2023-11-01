/*
** EPITECH PROJECT, 2023
** HandlingEvent.cpp
** File description:
** HandlingEvent
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::handleEvent()
    {
        struct rtype::Event event;

        while (_eventQueue.size() != 0) {
            event = _eventQueue.pop();
            switch (event.packetType) {
            case static_cast<uint8_t>(rtype::PacketType::CONNEXION):
                handleConnexion(event);
                break;
            case static_cast<uint8_t>(rtype::PacketType::MOVE):
                handleMove(event);
                break;
            case static_cast<uint8_t>(rtype::PacketType::DESTROY):
                handleDestroy(event);
                break;
            case static_cast<uint8_t>(rtype::PacketType::SHOOT):
                handleShoot(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_RES):
                handleTextureResponse(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION_RES):
                handleCollisionResponse(event);
                break;
            }
        }
    }
} // namespace RType::Server
