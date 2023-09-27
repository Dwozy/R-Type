/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingText
*/

#include "Registry.hpp"
#include "Components/Font.hpp"
#include "Components/Text.hpp"

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
                Fon.font.load(Fon.path);
                Tex.text.load(Tex.str, Fon.getFont(), Tex.size);
            }
        }
    }
}
