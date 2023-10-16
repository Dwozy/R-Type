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
#include "components/TransformComponent.hpp"

namespace GameEngine
{
    class ControlSystem
    {
      public:
        ControlSystem(){};
        ~ControlSystem() = default;

        void operator()(SparseArray<TransformComponent> &transforms,
                        SparseArray<ControllableComponent> &controllable);
    };
} // namespace GameEngine

#endif /* !CONTROLSYSTEM_HPP_ */
