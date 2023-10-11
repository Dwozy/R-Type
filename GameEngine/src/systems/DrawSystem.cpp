/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemDraw
*/
#include "systems/DrawSystem.hpp"
#include "components/TextComponent.hpp"
#include "components/TextureComponent.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <utility>
#include <variant>
#include <vector>

namespace GameEngine
{
    void DrawSystem::operator()(SparseArray<TextComponent> &texts,
                                SparseArray<TextureComponent> &textures,
                                SparseArray<TextureAnimatedComponent> &texturesA)
    {
        std::vector<std::variant<TextureComponent, TextComponent, TextureAnimatedComponent>> rend;
        _window.clear();

        for (size_t i = 0; i < texts.size(); i++) {
            auto &tex = texts[i];
            if (tex)
                rend.push_back(tex.value());
        }

        for (size_t i = 0; i < textures.size(); i++) {
            auto &tex = textures[i];
            if (tex)
                rend.push_back(tex.value());
        }

        for (size_t i = 0; i < texturesA.size(); i++) {
            auto &texA = texturesA[i];
            if (texA)
                rend.push_back(texA.value());
        }

        // std::sort(rend.begin(), rend.end(),
        //           [](const std::variant<TextureComponent, TextComponent, TextureAnimatedComponent> &a,
        //              const std::variant<TextureComponent, TextComponent, TextureAnimatedComponent> &b) {
        //               if (std::holds_alternative<TextureComponent>(a) &&
        //                   std::holds_alternative<TextureComponent>(b))
        //                   return std::get<TextureComponent>(a).renderLayer <
        //                          std::get<TextureComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextureComponent>(a) &&
        //                   std::holds_alternative<TextComponent>(b))
        //                   return std::get<TextureComponent>(a).renderLayer <
        //                          std::get<TextComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextComponent>(a) &&
        //                   std::holds_alternative<TextureComponent>(b))
        //                   return std::get<TextComponent>(a).renderLayer <
        //                          std::get<TextureComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextComponent>(a) &&
        //                   std::holds_alternative<TextComponent>(b))
        //                   return std::get<TextComponent>(a).renderLayer <
        //                          std::get<TextComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextureAnimatedComponent>(a) &&
        //                   std::holds_alternative<TextureAnimatedComponent>(b))
        //                   return std::get<TextureAnimatedComponent>(a).renderLayer <
        //                          std::get<TextureAnimatedComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextureAnimatedComponent>(a) &&
        //                   std::holds_alternative<TextureComponent>(b))
        //                   return std::get<TextureAnimatedComponent>(a).renderLayer <
        //                          std::get<TextureComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextureComponent>(a) &&
        //                   std::holds_alternative<TextureAnimatedComponent>(b))
        //                   return std::get<TextureComponent>(a).renderLayer <
        //                          std::get<TextureAnimatedComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextComponent>(a) &&
        //                   std::holds_alternative<TextureAnimatedComponent>(b))
        //                   return std::get<TextComponent>(a).renderLayer <
        //                          std::get<TextureAnimatedComponent>(b).renderLayer;
        //               if (std::holds_alternative<TextureAnimatedComponent>(a) &&
        //                   std::holds_alternative<TextComponent>(b))
        //                   return std::get<TextureAnimatedComponent>(a).renderLayer <
        //                          std::get<TextComponent>(b).renderLayer;
        //               return false;
        //           });

        for (const auto &item : rend) {
            if (std::holds_alternative<TextureComponent>(item)) {
                const auto &tex = std::get<TextureComponent>(item);
                _window.draw(tex.sprite.getSprite());
            } else if (std::holds_alternative<TextComponent>(item)) {
                const auto &tex = std::get<TextComponent>(item);
                _window.draw(tex.text.getText());
            } else if (std::holds_alternative<TextureAnimatedComponent>(item)) {
                const auto &tex = std::get<TextureAnimatedComponent>(item);
                _window.draw(tex.sprite.getSprite());
            }
        }
        _window.display();
    }
} // namespace GameEngine
