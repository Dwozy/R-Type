/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ShowHitboxSystem
*/

#include "systems/ShowHitboxSystem.hpp"

namespace GameEngine
{
    void ShowHitboxSystem::operator()(SparseArray<PositionComponent> &positions, SparseArray<CollisionComponent> &collisions)
    {
        for (std::size_t i = 0; i < positions.size(); i++)
        {
            auto &pos = positions[i];
            auto &col = collisions[i];

            if (!col || !pos)
                continue;
            if (col.value().isActive)
                _window.drawRect(col.value().collider, pos.value().position, Color(255, 0, 0, 100));
        }
        _window.display();
    }
}
