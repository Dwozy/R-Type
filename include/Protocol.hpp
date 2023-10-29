/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <cstdint>

namespace RType::Protocol
{
    static const uint32_t MAGIC_NUMBER = 0xA54CDEF5;

    enum class ComponentType : uint8_t {
        TRANSFORM = 1,
        COLLISION,
        TEXTURE,
    };

    enum class InputType : uint8_t {
        UP = 1,
        RIGHT,
        DOWN,
        LEFT,
        SHOOT
    };

    enum class TextureType : uint8_t { NONE = 1, PLAYER, SHOOT, MOB };

    struct HeaderDataPacket
    {
        uint32_t magicNumber = MAGIC_NUMBER;
        uint8_t packetType;
        uint16_t payloadSize;
    };

    struct TransformData
    {
        uint16_t id;
        float x;
        float y;
        float dx;
        float dy;
    };

    struct CollisionData
    {
        uint16_t id;
        float rectLeft;
        float rectTop;
        float rectWidth;
        float rectHeight;
        uint8_t layer;
    };

    struct TextureData
    {
        uint16_t id;
        uint8_t idTexture;
        uint16_t rectLeft;
        uint16_t rectTop;
        uint16_t rectWidth;
        uint16_t rectHeight;
        uint8_t renderLayer;
    };

    struct MoveData
    {
        uint16_t id;
        float x;
        float y;
        float dx;
        float dy;
    };

    struct ShootData
    {
        uint16_t id;
        float x;
        float y;
        float dx;
        float dy;
    };
} // namespace RType::Protocol

#endif
