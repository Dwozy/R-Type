/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemDraw
*/
#include "Systems.hpp"
#include "Components/RenderableComponent.hpp"
#include "Components/TextComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include <SFML/Graphics.hpp>
#include <variant>
#include <vector>
#include <utility>
#include <algorithm>

namespace GameEngine
{
    void SystemDraw(Registry &r, sf::RenderWindow &window)
    {
        auto &Text = r.getComponent<GameEngine::Text>();
        auto &Sprite = r.getComponent<GameEngine::Sprite>();
        auto &Renderable = r.getComponent<GameEngine::Renderable>();
        std::vector<std::pair<std::variant<GameEngine::Sprite, GameEngine::Text>, GameEngine::Renderable>> rend;
        window.clear();

        for (size_t i = 0; i < Text.size() && i < Renderable.size(); ++i) {
            auto &Tex = Text[i];
            auto &Render = Renderable[i];
            if (Tex && Render) {
                rend.emplace_back(std::make_pair(Tex.value(), Render.value()));
            }
        }

        for (size_t i = 0; i < Sprite.size() && i < Renderable.size(); ++i) {
            auto &Spr = Sprite[i];
            auto &Render = Renderable[i];
            if (Spr && Render) {
                rend.emplace_back(std::make_pair(Spr.value(), Render.value()));
            }
        }

        std::sort(rend.begin(), rend.end(), [](const std::pair<std::variant<GameEngine::Sprite, GameEngine::Text>, GameEngine::Renderable> &a, const std::pair<std::variant<GameEngine::Sprite, GameEngine::Text>, GameEngine::Renderable> &b) {
            return a.second.Renderpriority < b.second.Renderpriority;
        });

        for (const auto &item : rend) {
            if (std::holds_alternative<GameEngine::Sprite>(item.first)) {
                const auto &spr = std::get<GameEngine::Sprite>(item.first);
                window.draw(spr.sprite.getSprite());
            } else if (std::holds_alternative<GameEngine::Text>(item.first)) {
                const auto &tex = std::get<GameEngine::Text>(item.first);
                window.draw(tex.text.getText());
            }
        }
        window.display();
    }
}
