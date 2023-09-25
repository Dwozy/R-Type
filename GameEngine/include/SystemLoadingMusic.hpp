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
    class SystemLoadingMusic : public SystemBase
    {
        public:
            SystemLoadingMusic(GameEngine &gameEngine): SystemBase(gameEngine) {};
        protected:
           void _updateSingle(const Entity &entity) override {};
    };
}

#endif /* !SYSTEMLOADINGMUSIC_HPP_ */
