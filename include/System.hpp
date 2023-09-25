/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System
*/

#ifndef SYSTEM_HPP_
    #define SYSTEM_HPP_
    #include <set>
    #include "Entity.hpp"

namespace GameEngine
{
    class GameEngine;

    /// @brief Base of the systems class. Inherit from it to create new systems.
    class SystemBase
    {
        public:
            /// @brief Constructor for the system.
            /// @param gameEngine Reference to the game engine.
            SystemBase(GameEngine &gameEngine): _gameEngine(gameEngine) {};

            /// @brief Updates the system for every registered entity. No need to modify it when inherited.
            virtual void update()
            {
                for (const Entity &entity : entities)
                    _updateSingle(entity);
            };

            /// @brief Set of entities which are registered to the system.
            std::set<Entity> entities;
        protected:
            /// @brief Update method for a single entity. Will be called in update. Part to modify when inherited.
            /// @param entity Entity to update.
            virtual void _updateSingle(const Entity &entity) {};

            GameEngine &_gameEngine;
    };
}

#endif /* !SYSTEM_HPP_ */
