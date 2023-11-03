/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GravitySystem
*/

#include "systems/GravitySystem.hpp"

namespace GameEngine
{
    void GravitySystem::operator()(SparseArray<GravityComponent> &gravity)
    {
        _currentDeltaTime += _deltaTime;
        for (size_t i = 0; i < gravity.size(); ++i) {
            auto &grav = gravity[i];
            if (!(_currentDeltaTime >= 0.001))
                return;
            if (grav) {
                if (grav->isActive == true)
                    grav->cumulatedGVelocity += grav->gravityForce;
            }
        }
        _currentDeltaTime = 0;
    }
} // namespace GameEngine
