/*
** EPITECH PROJECT, 2023
** DamageSystem.cpp
** File description:
** DamageSystem
*/

#include "systems/DamageSystem.hpp"
#include "Entity.hpp"

namespace GameEngine
{
    void DamageSystem::operator()(SparseArray<DamageComponent> &damages, SparseArray<HealthComponent> &healths)
    {
        for (std::size_t i = 0; i < damages.size(); i++) {
            auto &damage = damages[i];
            auto &health = healths[i];
            if (!damage || !health)
                continue;
            while (damage.value().listDamage.size() != 0) {
                health.value().health -= damage.value().listDamage.back();
                damage.value().listDamage.pop_back();
            }
            if (health.value().health <= 0)
                _eventManager.getHandler<std::size_t &>(static_cast<EventType>(Event::GetDestroy)).publish(i);
        }
    }
} // namespace GameEngine
