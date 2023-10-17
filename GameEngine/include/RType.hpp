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
    static const std::size_t HEADER_SIZE = 8;
    static const uint32_t MAGIC_NUMBER = 0xA54CDEF5;

    enum class PacketType : uint8_t {
        ROOM = 1,
        STRING = 2,
        ENTITY = 3,
        CONNEXION = 4,
        CONNECTED = 5,
        MOVE = 6,
        SHOOT = 7,
        CREATE_PLAYER = 8,
        DISCONNEXION = 9
    };

    struct Event
    {
        uint8_t packetType;
        std::any data;
    };

    struct Entity
    {
        uint16_t id; // client
        uint32_t positionX;
        uint32_t positionY;
        float directionX;
        float directionY;
    };

    struct Move
    {
        uint16_t id;
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
        uint16_t positionX;
        uint16_t positionY;
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
