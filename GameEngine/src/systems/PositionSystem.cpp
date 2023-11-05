/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PositionSystem
*/

#include "systems/PositionSystem.hpp"

namespace GameEngine
{
    void PositionSystem::operator()(SparseArray<TransformComponent> &transforms,
        SparseArray<TextureComponent> &textures, SparseArray<GravityComponent> &gravities)
    {
        for (size_t i = 0; i < transforms.size(); i++) {
            auto &tsf = transforms[i];
            auto &tex = textures[i];
            auto &grav = gravities[i];
            if (tsf)
                tsf.value().position +=
                    (tsf.value().velocity + (grav && grav->isActive ? grav->cumulatedGVelocity : Vector2<float>())) *
                    _deltaTime;
            if (tsf && tex)
                tex.value().sprite.setPosition(tsf.value().position);
        }
    }
} // namespace GameEngine
