/*
** EPITECH PROJECT, 2023
** RType.hpp
** File description:
** RType
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include <map>
#include <string>
#include <utility>
#include <cstdint>
#include <any>

namespace rtype
{
    static const std::size_t MAX_BUFFER_SIZE = 65535;
    static const std::size_t HEADER_SIZE = 8;
    static const uint32_t MAGIC_NUMBER = 0xA54CDEF5;
    static const float PLAYER_SPEED = 25.0f;

    enum class PacketType : uint8_t {
        ROOM = 1,
        STRING,
        ENTITY,
        CONNEXION,
        CONNECTED,
        MOVE,
        SHOOT,
        CREATE_PLAYER,
        DESTROY
    };

    enum class TextureType : uint8_t { NONE = 1, PLAYER, SHOOT, MOB };

    struct Event
    {
        uint8_t packetType;
        std::any data;
    };

    struct Entity
    {
        uint16_t id;
        uint8_t idTexture;
        // uint8_t lifePoint;
        float positionX;
        float positionY;
        float directionX;
        float directionY;
    };

    struct EntityId
    {
        uint16_t id;
    };

    struct Shoot
    {
        uint16_t id;
        float positionX;
        float positionY;
    };

    struct HeaderDataPacket
    {
        uint32_t magicNumber = MAGIC_NUMBER;
        uint8_t packetType;
        uint16_t payloadSize;
    };

    struct Room
    {
        uint16_t id; // unique
        uint8_t slots;
        uint8_t slotsUsed;
        uint8_t stageLevel;
        // std::string name;
        // std::map<std::size_t, struct Player> listPlayers;
    };
} // namespace rtype

#endif /* !RTYPE_HPP_ */
