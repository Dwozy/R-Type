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
