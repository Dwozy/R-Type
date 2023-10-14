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
#include "components/TransformComponent.hpp"
#include "components/TextureComponent.hpp"

namespace GameEngine
{
    class PositionSystem
    {
      public:
        PositionSystem(const float &deltaTime) : _deltaTime(deltaTime){};
        ~PositionSystem() = default;

        void operator()(SparseArray<TransformComponent> &transforms,
                        SparseArray<TextureComponent> &textures);

      private:
        const float &_deltaTime;
    };
} // namespace GameEngine

#endif /* !POSITIONSYSTEM_HPP_ */
