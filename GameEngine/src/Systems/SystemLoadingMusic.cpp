/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingMusic
*/

#include "Registry.hpp"
#include "Components/Music.hpp"

namespace GameEngine
{
    void SystemLoadingMusic(Registry &r)
    {
        auto &Music = r.getComponent<GameEngine::Music>();
        for (size_t i = 0; i < Music.size(); ++i) {
            auto &Mus = Music[i];
            if (Mus) {
                Mus.music.load(Mus.path);
            }
        }
    }
}
