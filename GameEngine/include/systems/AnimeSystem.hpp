/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimeSystem
*/

#ifndef ANIMESYSTEM_HPP_
#define ANIMESYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"


namespace GameEngine
{
    class AnimeSystem {
        public:
            AnimeSystem(const float &deltaTime) : _deltaTime(deltaTime), _currentDeltaTime(0.0f) {};
            ~AnimeSystem() = default;
            void operator()(SparseArray<TextureComponent> &texture);
        private:
            const float &_deltaTime;
            float _currentDeltaTime;
    };
}

#endif /* !ANIMESYSTEM_HPP_ */
