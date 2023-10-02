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
    #include "Components/TextureComponent.hpp"

namespace GameEngine
{
    void positionSystem(Registry &registry, SparseArray<GameEngine::PositionComponent> &positions, SparseArray<GameEngine::VelocityComponent> &velocities, SparseArray<GameEngine::TextureComponent> &textures);
}

#endif /* !POSITIONSYSTEM_HPP_ */
