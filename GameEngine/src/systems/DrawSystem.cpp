/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemDraw
*/
#include <SFML/Graphics.hpp>
#include <variant>
#include <vector>
#include <utility>
#include <algorithm>
#include "Systems.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"

namespace GameEngine
{
    void SystemDraw(Registry &r, sf::RenderWindow &window)
    {
        auto &text = r.getComponent<GameEngine::TextComponent>();
        auto &textures = r.getComponent<GameEngine::TextureComponent>();
        std::vector<std::variant<GameEngine::TextureComponent, GameEngine::TextComponent>> rend;
        window.clear();

        for (size_t i = 0; i < text.size(); i++)
        {
            auto &tex = text[i];
            if (tex)
                rend.push_back(tex.value());
        }

        for (size_t i = 0; i < textures.size(); i++)
        {
            auto &tex = textures[i];
            if (tex)
                rend.push_back(tex.value());
        }

        std::sort(rend.begin(), rend.end(), [](const std::variant<GameEngine::TextureComponent, GameEngine::TextComponent> &a, const std::variant<GameEngine::TextureComponent, GameEngine::TextComponent> &b)
        {
            if (std::holds_alternative<GameEngine::TextureComponent>(a) && std::holds_alternative<GameEngine::TextureComponent>(b))
                return std::get<GameEngine::TextureComponent>(a).renderLayer < std::get<GameEngine::TextureComponent>(b).renderLayer;
            if (std::holds_alternative<GameEngine::TextureComponent>(a) && std::holds_alternative<GameEngine::TextComponent>(b))
                return std::get<GameEngine::TextureComponent>(a).renderLayer < std::get<GameEngine::TextComponent>(b).renderLayer;
            if (std::holds_alternative<GameEngine::TextComponent>(a) && std::holds_alternative<GameEngine::TextureComponent>(b))
                return std::get<GameEngine::TextComponent>(a).renderLayer < std::get<GameEngine::TextureComponent>(b).renderLayer;
            if (std::holds_alternative<GameEngine::TextComponent>(a) && std::holds_alternative<GameEngine::TextComponent>(b))
                return std::get<GameEngine::TextComponent>(a).renderLayer < std::get<GameEngine::TextComponent>(b).renderLayer;
            return false;
        });

        for (const auto &item : rend)
        {
            if (std::holds_alternative<GameEngine::TextureComponent>(item))
            {
                const auto &tex = std::get<GameEngine::TextureComponent>(item);
                window.draw(tex.sprite.getSprite());
            }
            else if (std::holds_alternative<GameEngine::TextComponent>(item))
            {
                const auto &tex = std::get<GameEngine::TextComponent>(item);
                window.draw(tex.text.getText());
            }
        }
        window.display();
    }
}
