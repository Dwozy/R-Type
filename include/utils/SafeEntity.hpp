/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SafeEntity
*/

#ifndef SAFEENTITY_HPP_
    #define SAFEENTITY_HPP_
    #include "GameEngine.hpp"

namespace GameEngine
{
    class SafeEntity {
        public:
            SafeEntity(GameEngine &gameEngine);
            ~SafeEntity();

            Entity get() { return _entity; };
        private:
            Entity _entity;
            GameEngine &_gameEngine;
    };
}

#endif /* !SAFEENTITY_HPP_ */
