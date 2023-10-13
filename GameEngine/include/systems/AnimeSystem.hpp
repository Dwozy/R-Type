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
#include "components/TextureAnimatedComponent.hpp"


namespace GameEngine
{
    class AnimeSystem {
        public:
            AnimeSystem() {};
            ~AnimeSystem() = default;
            void operator()(SparseArray<TextureAnimatedComponent> &texture);
    };
}

#endif /* !ANIMESYSTEM_HPP_ */
