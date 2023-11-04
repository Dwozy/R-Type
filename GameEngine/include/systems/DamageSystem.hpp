/*
** EPITECH PROJECT, 2023
** DamageSystem.hpp
** File description:
** DamageSystem
*/

#ifndef DAMAGESYSTEM_HPP_
#define DAMAGESYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "components/HealthComponent.hpp"
#include "components/DamageComponent.hpp"

namespace GameEngine
{
    class DamageSystem
    {
      public:
        DamageSystem(EventManager &eventManager) : _eventManager(eventManager){};
        ~DamageSystem() = default;

        void operator()(SparseArray<DamageComponent> &damages, SparseArray<HealthComponent> &healths);

      protected:
      private:
        EventManager &_eventManager;
    };
} // namespace GameEngine
#endif /* !DAMAGESYSTEM_HPP_ */
