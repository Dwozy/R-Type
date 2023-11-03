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

namespace RType
{
    static const std::size_t MAX_BUFFER_SIZE = 65535;
    static const std::size_t HEADER_SIZE = 8;
    static const uint32_t MAGIC_NUMBER = 0xA54CDEF5;
    static const float PLAYER_SPEED = 100.0f;

    enum class PacketType : uint8_t { STRING = 10, CONNEXION, DESTROY };

    enum class TextureType : uint8_t { NONE = 1, PLAYER, SIMPLE_SHOOT, CHARGED_SHOOT, SIMPLE_MOB, MEDIUM_MOB };

    struct Event
    {
        uint8_t packetType;
        unsigned short port;
        std::any data;
    };
} // namespace RType

#endif /* !RTYPE_HPP_ */
