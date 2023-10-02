/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingText
*/

#include "Components/FontComponent.hpp"
#include "Components/TextComponent.hpp"
#include "Systems.hpp"

namespace GameEngine
{

    void SystemLoadingText(Registry &r)
    {
        auto &Font = r.getComponent<GameEngine::Font>();
        auto &Text = r.getComponent<GameEngine::Text>();
        for (size_t i = 0; i < Font.size() && i < Text.size (); ++i) {
            auto &Fon = Font[i];
            auto &Tex = Text[i];
            if (Fon && Tex) {
                Fon.value().font.load(Fon.value().path);
                Tex.value().text.load(Tex.value().str, Fon.value().font.getFont(), Tex.value().size);
            }
        }
    }
}
