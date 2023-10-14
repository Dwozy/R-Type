/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CoLLisionComponent
*/

#ifndef COLLISIONCOMPONENT_HPP_
#define COLLISIONCOMPONENT_HPP_
#include "Registry.hpp"
#include <functional>
#include <vector>

namespace GameEngine
{
    struct CollisionComponent
    {
        Rectf collider;
        std::vector<std::function<void(const std::size_t &entityId)>> actions;
        std::size_t layer;
        bool isActive = true;

        template <typename Function, class... Components>
        void addAction(Registry &registry, const Function &function)
        {
            std::function<void(const std::size_t &entityId)> action =
                [function, &registry](const std::size_t &entityId) {
                    function(entityId, registry.getComponent<Components>()...);
                };
            actions.push_back(action);
        };
    };
} // namespace GameEngine

#endif /* !COLLISIONCOMPONENT_HPP_ */
