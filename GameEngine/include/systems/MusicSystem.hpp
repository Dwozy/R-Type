/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MusicSystem
*/

#ifndef MUSICSYSTEM_HPP_
#define MUSICSYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "components/MusicComponent.hpp"

namespace GameEngine
{
    class MusicSystem
    {
      public:
        MusicSystem(){};
        ~MusicSystem() = default;

        void operator()(SparseArray<MusicComponent> &musicComponents);
    };
} // namespace GameEngine

#endif /* !MUSICSYSTEM_HPP_ */
