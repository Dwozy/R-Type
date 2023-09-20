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
    class ISystem
    {
        public:
            ~ISystem() = default;

            virtual void update() = 0;
        protected:
            virtual void _updateSingle(const Entity &entity) = 0;
    };

    class SystemBase : public ISystem
    {
        public:
            SystemBase(/*GameEngine gameEngine*/)/*: _gameEngine(gameEngine)*/ {};

            virtual void update() override
            {
                for (const Entity &entity : entities)
                    _updateSingle(entity);
            };

            std::set<Entity> entities;
        protected:
            virtual void _updateSingle(const Entity &entity) override {};

            /*GameEngine _gameEngine;*/
    };
}

#endif /* !SYSTEM_HPP_ */
