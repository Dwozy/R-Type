/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PositionSystem
*/

#include "systems/PositionSystem.hpp"

namespace GameEngine
{
    void PositionSystem::operator()(
        SparseArray<TransformComponent> &transforms, SparseArray<TextureComponent> &textures)
    {
        for (size_t i = 0; i < transforms.size(); i++) {
            auto &tsf = transforms[i];
            auto &tex = textures[i];
            if (tsf) {
                tsf.value().position.x += tsf.value().velocity.x * _deltaTime;
                tsf.value().position.y += tsf.value().velocity.y * _deltaTime;
            }
            if (tsf && tex)
                tex.value().sprite.setPosition(tsf.value().position);
        }
    }
} // namespace GameEngine
