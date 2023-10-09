/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CoLLisionComponent
*/

#ifndef COLLISIONCOMPONENT_HPP_
#define COLLISIONCOMPONENT_HPP_
#include <functional>
#include <vector>
#include "Registry.hpp"

namespace GameEngine
{
    class CollisionComponent
    {
        public:
            CollisionComponent() {};
            ~CollisionComponent() = default;
            std::vector<std::function<void()>> actions;
            std::size_t layer;

            template <typename Function, class... Components>
            void addAction(const Registry &registry, const Function &function)
            {
                std::function<void()> action = [this, function, registry]() {
                    function(registry.getComponent<Components>()...);
                };
                actions.push_back(action);
            };
    };
} // namespace GameEngine

#endif /* !COLLISIONCOMPONENT_HPP_ */
