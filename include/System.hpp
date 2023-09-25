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

    class SystemBase
    {
        public:
            SystemBase(GameEngine &gameEngine): _gameEngine(gameEngine) {};

            virtual void update()
            {
                for (const Entity &entity : entities)
                    _updateSingle(entity);
            };

            std::set<Entity> entities;
        protected:
            virtual void _updateSingle(const Entity &entity) {};

            GameEngine &_gameEngine;
    };
}

#endif /* !SYSTEM_HPP_ */
