/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingText
*/

#ifndef SYSTEMLOADINGTEXT_HPP_
    #define SYSTEMLOADINGTEXT_HPP_
    #include <set>
    #include "Entity.hpp"
    #include "System.hpp"

namespace GameEngine
{
    class SystemLoadingText : public ISystem
    {
        public:
            SystemLoadingText(GameEngine &gameEngine): _gameEngine(gameEngine) {};
            virtual void update() override
            {
                for (const Entity &entity : entities)
                    _updateSingle(entity);
            };
            std::set<Entity> entities;
        protected:
            virtual void _updateSingle(const Entity &entity) override {};

            GameEngine &_gameEngine;
    };
};

#endif /* !SYSTEMLOADINGTEXT_HPP_ */
