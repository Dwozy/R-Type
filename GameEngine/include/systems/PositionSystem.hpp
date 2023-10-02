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
    #include "components/TextureComponent.hpp"
    #include "GameEngine.hpp"

namespace GameEngine
{
    void positionSystem(GameEngine &gameEngine, SparseArray<PositionComponent> &positions, SparseArray<VelocityComponent> &velocities, SparseArray<TextureComponent> &textures);
}

#endif /* !POSITIONSYSTEM_HPP_ */
