/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemDraw
*/

#include "Systems.hpp"
#include "Components/Window.hpp"
#include "Components/Text.hpp"
#include "Components/Sprite.hpp"
#include <SFML/Graphics.hpp>

namespace GameEngine
{

    void SystemDraw(Registry &r, sf::RenderWindow &window)
    {
        auto &Text = r.getComponent<GameEngine::Text>();
        auto &Sprite = r.getComponent<GameEngine::Sprite>();
        window.clear();
        for (size_t i = 0; i < Text.size(); ++i) {
            auto &Tex = Text[i];
            if (Tex)
                window.draw(Tex.value().text.getText());
        }
        for (size_t i = 0; i < Sprite.size(); ++i) {
            auto &Spr = Sprite[i];
            if (Spr)
                window.draw(Spr.value().sprite.getSprite());
        }
        window.display();
    }
}
