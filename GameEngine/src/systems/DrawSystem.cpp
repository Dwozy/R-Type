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
        auto &text = r.getComponent<GameEngine::Text>();
        auto &textures = r.getComponent<GameEngine::TextureComponent>();
        std::vector<std::variant<GameEngine::TextureComponent, GameEngine::Text>> rend;
        // std::vector<std::variant<GameEngine::TextureComponent, GameEngine::Text>> rend;
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

        std::sort(rend.begin(), rend.end(), [](const std::variant<GameEngine::TextureComponent, GameEngine::Text> &a, const std::variant<GameEngine::TextureComponent, GameEngine::Text> &b)
        {
            if (std::holds_alternative<GameEngine::TextureComponent>(a) && std::holds_alternative<GameEngine::TextureComponent>(b))
                return std::get<GameEngine::TextureComponent>(a).renderLayer < std::get<GameEngine::TextureComponent>(b).renderLayer;
            if (std::holds_alternative<GameEngine::TextureComponent>(a) && std::holds_alternative<GameEngine::Text>(b))
                return std::get<GameEngine::TextureComponent>(a).renderLayer < std::get<GameEngine::Text>(b).renderLayer;
            if (std::holds_alternative<GameEngine::Text>(a) && std::holds_alternative<GameEngine::TextureComponent>(b))
                return std::get<GameEngine::Text>(a).renderLayer < std::get<GameEngine::TextureComponent>(b).renderLayer;
            if (std::holds_alternative<GameEngine::Text>(a) && std::holds_alternative<GameEngine::Text>(b))
                return std::get<GameEngine::Text>(a).renderLayer < std::get<GameEngine::Text>(b).renderLayer;
            return false;
        });

        for (const auto &item : rend)
        {
            if (std::holds_alternative<GameEngine::TextureComponent>(item))
            {
                const auto &tex = std::get<GameEngine::TextureComponent>(item);
                window.draw(tex.sprite.getSprite());
            }
            else if (std::holds_alternative<GameEngine::Text>(item))
            {
                const auto &tex = std::get<GameEngine::Text>(item);
                window.draw(tex.text.getText());
            }
        }
        window.display();
    }
}
