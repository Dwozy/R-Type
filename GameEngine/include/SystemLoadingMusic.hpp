/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingMusic
*/

#ifndef SYSTEMLOADINGMUSIC_HPP_
    #define SYSTEMLOADINGMUSIC_HPP_
    #include <set>
    #include "Entity.hpp"
    #include "System.hpp"

namespace GameEngine
{
    class SystemLoadingMusic : public ISystem
    {
        public:
            SystemLoadingMusic(GameEngine &gameEngine): _gameEngine(gameEngine) {};
            virtual void update() override
            {
                for (const Entity &entity : entities)
                    _updateSingle(entity);
            };
            std::set<Entity> entities;
        protected:
            virtual void _updateSingle(const Entity &entity) override {};
    };
}

#endif /* !SYSTEMLOADINGMUSIC_HPP_ */
