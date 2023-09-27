/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingTexture
*/

#include "Registry.hpp"
#include "Components/Texture.hpp"
#include "Components/Sprite.hpp"

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
                Tex.texture.load(Tex.path);
                Spr.sprite.load(Tex.getTexture());
            }
        }
    }
}
