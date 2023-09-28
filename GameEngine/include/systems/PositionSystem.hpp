/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_
    #include "Registry.hpp"
    #include "components/PositionComponent.hpp"
    #include "components/VelocityComponent.hpp"

namespace GameEngine
{
    void positionSystem(Registry &registry);
}

#endif /* !POSITIONSYSTEM_HPP_ */