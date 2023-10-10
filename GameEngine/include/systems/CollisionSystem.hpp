/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
    #define COLLISIONSYSTEM_HPP_
    #include "GameEngine.hpp"
    #include "Registry.hpp"
    #include "components/CollisionComponent.hpp"

namespace GameEngine
{
    class CollisionSystem
    {
      public:
        CollisionSystem(){};
        ~CollisionSystem() = default;

        void operator()(SparseArray<CollisionComponent> &collisions);
    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */
