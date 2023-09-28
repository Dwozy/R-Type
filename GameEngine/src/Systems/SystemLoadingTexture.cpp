/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingTexture
*/

#include "Components/Texture.hpp"
#include "Components/Sprite.hpp"
#include "Systems.hpp"

namespace GameEngine
{

    void SystemLoadingTexture(Registry &r)
    {
        auto &Texture = r.getComponent<GameEngine::Texture>();
        auto &Sprite = r.getComponent<GameEngine::Sprite>();
        for (size_t i = 0; i < Texture.size() && i < Sprite.size (); ++i) {
            auto &Tex = Texture[i];
            auto &Spr = Sprite[i];
            if (Tex && Spr) {
                Tex.value().texture.load(Tex.value().path);
                Spr.value().sprite.load(Tex.value().texture.getTexture());
            }
        }
    }
}
