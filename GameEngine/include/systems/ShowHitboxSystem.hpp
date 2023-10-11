/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ShowHitboxSystem
*/

#ifndef SHOWHITBOXSYSTEM_HPP_
#define SHOWHITBOXSYSTEM_HPP_
#include "utils/SfmlTypes.hpp"
#include "SparseArray.hpp"
#include "components/CollisionComponent.hpp"
#include "components/PositionComponent.hpp"

namespace GameEngine
{
    class ShowHitboxSystem
    {
      public:
        ShowHitboxSystem(Window &window) : _window(window){};
        ~ShowHitboxSystem() = default;

        void operator()(SparseArray<PositionComponent> &positions, SparseArray<CollisionComponent> &collisions);

      private:
        Window &_window;
    };
} // namespace GameEngine

#endif /* !SHOWHITBOXSYSTEM_HPP_ */
