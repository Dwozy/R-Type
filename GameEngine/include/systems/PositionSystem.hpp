/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PositionSystem
*/

#ifndef POSITIONSYSTEM_HPP_
#define POSITIONSYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "components/PositionComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/VelocityComponent.hpp"

namespace GameEngine
{
    class PositionSystem
    {
      public:
        PositionSystem(const float &deltaTime) : _deltaTime(deltaTime){};
        ~PositionSystem() = default;

        void operator()(SparseArray<PositionComponent> &positions,
                        SparseArray<VelocityComponent> &velocities,
                        SparseArray<TextureComponent> &textures);

      private:
        const float &_deltaTime;
    };
} // namespace GameEngine

#endif /* !POSITIONSYSTEM_HPP_ */
