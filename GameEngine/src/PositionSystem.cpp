/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PositionSystem
*/

#include "systems/PositionSystem.hpp"
#include <iostream>

namespace GameEngine
{
    void positionSystem(Registry &registry)
    {
        auto &positions = registry.getComponent<PositionComponent>();
        auto &velocities = registry.getComponent<VelocityComponent>();

        for (size_t i = 0; i < positions.size() && i < velocities.size (); i++) {
            auto &pos = positions[i];
            auto &vel = velocities[i];
            if (pos && vel)
                pos.value().position += vel.value().velocity;
        }
    }
}

