/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CollisionSystem
*/

#include "systems/CollisionSystem.hpp"

namespace GameEngine
{
    void CollisionSystem::operator()(SparseArray<CollisionComponent> &collisions)
    {
        for (std::size_t i = 0; i < collisions.size(); i++) {
            auto &col = collisions[i];

            if (!col)
                continue;
            if (!col.value().isActive)
                continue;
            for (std::size_t j = 0; j < col.value().actions.size(); j++)
                col.value().actions[j](i);
        }
    }
} // namespace GameEngine
