/*
** EPITECH PROJECT, 2023
** RType.hpp
** File description:
** RType
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/serialization.hpp>
#include <map>
#include <string>
#include <utility>

namespace rtype
{

    const uint32_t MAGIC_NUMBER = 0xA54CDEF5;

    struct Player
    {
        std::string name;
    };

    struct Entity
    {
        std::pair<float, float> position;
        std::pair<float, float> direction;
        std::size_t lifePoint;
        struct Player playerInfo;
    };

    struct HeaderDataPacket
    {
        uint32_t magicNumber = MAGIC_NUMBER;
        uint8_t packetType;
        uint16_t payloadSize;

        template <typename Archive> void serialize(Archive &ar, const unsigned)
        {
            ar &magicNumber;
            ar &packetType;
            ar &payloadSize;
        }
    };

    struct Room
    {
        std::size_t id; // unique
        std::size_t slots;
        std::size_t slotsLeft;
        std::string name;
        std::size_t stageLevel;
        std::map<std::size_t, struct Player> listPlayers;
    };
} // namespace rtype

#endif /* !RTYPE_HPP_ */
