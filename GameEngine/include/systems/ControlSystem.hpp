/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ControlSystem
*/

#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "components/ControllableComponent.hpp"
#include "components/VelocityComponent.hpp"

namespace GameEngine
{
    class ControlSystem
    {
      public:
        ControlSystem(){};
        ~ControlSystem() = default;

        void operator()(SparseArray<VelocityComponent> &velocities, SparseArray<ControllableComponent> &controllable);
    };
} // namespace GameEngine

#endif /* !CONTROLSYSTEM_HPP_ */
