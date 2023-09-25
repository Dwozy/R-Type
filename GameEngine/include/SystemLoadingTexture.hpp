/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingTexture
*/

#ifndef SYSTEMLOADINGTEXTURE_HPP_
    #define SYSTEMLOADINGTEXTURE_HPP_
    #include <set>
    #include "Entity.hpp"
    #include "System.hpp"

namespace GameEngine
{
    class SystemLoadingTexture : public ISystem
    {
        public:
            SystemLoadingTexture(GameEngine &gameEngine): _gameEngine(gameEngine) {};
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
}

#endif /* !SYSTEMLOADINGTEXTURE_HPP_ */
