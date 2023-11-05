/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** MusicSystem
*/

#include "systems/MusicSystem.hpp"

namespace GameEngine
{
    void MusicSystem::operator()(SparseArray<MusicComponent> &musicComponents)
    {
        for (std::size_t i = 0; i < musicComponents.size(); i++) {
            auto &currentMusicComponent = musicComponents[i];
            if (!currentMusicComponent)
                continue;
            if (currentMusicComponent.value().music != nullptr)
                currentMusicComponent.value().music->play();
        }
    }
}
