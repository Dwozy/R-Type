/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PositionSystem
*/

#include "systems/PositionSystem.hpp"

namespace GameEngine
{
    void PositionSystem::operator()(SparseArray<PositionComponent> &positions,
                                    SparseArray<VelocityComponent> &velocities,
                                    SparseArray<TextureComponent> &textures)
    {
        for (size_t i = 0; i < positions.size(); i++) {
            auto &pos = positions[i];
            auto &vel = velocities[i];
            auto &tex = textures[i];
            if (pos && vel && tex) {
                pos.value().position +=
                    vel.value().velocity * _deltaTime;
                tex.value().sprite.setPosition(pos.value().position);
            } else if (pos && tex)
                tex.value().sprite.setPosition(pos.value().position);
        }
    }
} // namespace GameEngine
