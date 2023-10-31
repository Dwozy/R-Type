/*
** EPITECH PROJECT, 2023
** Callback.cpp
** File description:
** Callback
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::playerCollisionCallback(const std::size_t &entityId,
        SparseArray<GameEngine::CollisionComponent> &collisions,
        SparseArray<GameEngine::TransformComponent> &transforms)
    {
        auto &selfCol = collisions[entityId];
        auto &selfTsf = transforms[entityId];

        if (!selfCol || !selfTsf)
            return;
        for (std::size_t i = 0; i < collisions.size(); i++) {
            if (i == entityId)
                continue;
            auto &col = collisions[i];
            auto &tsf = transforms[i];

            if (!col || !tsf || !col.value().isActive || col.value().layer != 25)
                continue;
            selfCol.value().collider.handleCollisionFromRect(
                selfTsf.value().position, col.value().collider, tsf.value().position);
        }
    }

} // namespace RType::Client
