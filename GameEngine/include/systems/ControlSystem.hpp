/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ControlSystem
*/

#ifndef CONTROLSYSTEM_HPP_
    #define CONTROLSYSTEM_HPP_
    #include "Registry.hpp"
    #include "components/ControllableComponent.hpp"
    #include "components/VelocityComponent.hpp"
    #include "GameEngine.hpp"

namespace GameEngine
{
    void controlSystem(GameEngine &gameEngine, SparseArray<VelocityComponent> &velocities, SparseArray<ControllableComponent> &controllable);
}

#endif /* !CONTROLSYSTEM_HPP_ */