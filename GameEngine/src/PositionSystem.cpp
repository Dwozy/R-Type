/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PositionSystem
*/

#include "systems/PositionSystem.hpp"

namespace GameEngine
{
    void positionSystem(Registry &registry, SparseArray<GameEngine::PositionComponent> &positions, SparseArray<GameEngine::VelocityComponent> &velocities, SparseArray<GameEngine::TextureComponent> &textures)
    {
        for (size_t i = 0; i < positions.size() && i < velocities.size (); i++) {
            auto &pos = positions[i];
            auto &vel = velocities[i];
            auto &tex = textures[i];
            if (pos && vel && tex)
            {
                pos.value().position += vel.value().velocity;
                tex.value().sprite.setPosition(pos.value().position);
            }
        }
    }
}

