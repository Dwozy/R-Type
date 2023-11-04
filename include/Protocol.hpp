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
        CONTROLLABLE,
        INPUT,
        COLLISION_RES,
        TEXTURE_RES,
        TEXTURE_STATE
    };

    enum class PacketType : uint8_t { STRING = 10, CONNEXION, DESTROY, SCORE };

    enum class InputType : uint8_t { UP = 0, RIGHT, DOWN, LEFT, SHOOT };

    enum class TextureType : uint8_t { NONE = 1, PLAYER, SIMPLE_SHOOT, CHARGED_SHOOT, SIMPLE_MOB, MEDIUM_MOB };

    struct InputData
    {
        uint16_t id;
        uint8_t inputId;
        uint8_t state;
    };

    struct ScoreData
    {
        uint16_t score;
    };

    struct StatePlayerData
    {
        uint16_t id;
        uint8_t invincibility;
    };

    struct ControllableData
    {
        uint16_t id;
    };

    struct EntityIdData
    {
        uint16_t id;
    };

    struct HeaderDataPacket
    {
        uint32_t magicNumber = MAGIC_NUMBER;
        uint8_t packetType;
        uint16_t payloadSize;
    };

    struct CollisionResponse
    {
        uint16_t id;
    };

    struct TextureResponse
    {
        uint16_t id;
        uint16_t idTexture;
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
        uint8_t idCallback;
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
        uint8_t idOrderTexture;
        uint16_t rectLeft;
        uint16_t rectTop;
        uint16_t rectWidth;
        uint16_t rectHeight;
        uint16_t rectTextureLeft;
        uint16_t rectTextureTop;
        uint16_t rectTextureWidth;
        uint16_t rectTextureHeight;
        uint8_t renderLayer;
        uint8_t isAnimated;
        float animationSpeed;
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
