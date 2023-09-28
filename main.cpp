/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <iostream>
#include <cstdlib>
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "Components/Font.hpp"
#include "Components/Texture.hpp"
#include "Components/Sprite.hpp"
#include "Components/Music.hpp"
#include "Components/Text.hpp"
#include "utils/Vector.hpp"
#include "Systems.hpp"

void testSystem(Registry &registry, SparseArray<int> &ints, SparseArray<float> &floats)
{
    for (std::size_t i = 0; i < ints.size(); i++)
    {
        if (ints[i].has_value())
            std::cout << i << ". " << ints[i].value() << std::endl;
        else
            std::cout << i << ". none" << std::endl;
    }
    for (std::size_t i = 0; i < floats.size(); i++)
    {
        if (floats[i].has_value())
            std::cout << i << ". " << floats[i].value() << std::endl;
        else
            std::cout << i << ". none" << std::endl;
    }
}

int main()
{
    Registry registry;
    Entity entity = registry.spawnEntity();
    Entity entity2 = registry.spawnEntity();
    Entity entity3 = registry.spawnEntity();
    Entity entity4 = registry.spawnEntity();
    auto &Texture = registry.registerComponent<GameEngine::Texture>();
    auto &Sprite = registry.registerComponent<GameEngine::Sprite>();
    //auto &Music = registry.registerComponent<GameEngine::Music>();
    auto &Font = registry.registerComponent<GameEngine::Font>();
    auto &Text = registry.registerComponent<GameEngine::Text>();
    registry.addComponent<GameEngine::Texture>(entity, GameEngine::Texture{"testFolder/slime.png", GameEngine::Vector2<int>{150, 150}, GameEngine::SFTexture()});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{GameEngine::SFSprite()});
    registry.addComponent<GameEngine::Font>(entity2, GameEngine::Font{"testFolder/8-bit fortress.ttf", GameEngine::SFFont()});
    registry.addComponent<GameEngine::Text>(entity2, GameEngine::Text{"hello world", 20, GameEngine::Vector2<int>{300, 0}, GameEngine::SFText()});
    registry.addSystem<std::function<void(Registry &)>>(GameEngine::SystemLoadingTexture);
    registry.addSystem<std::function<void(Registry &)>>(GameEngine::SystemLoadingText);
    registry.addSystem<std::function<void(Registry &)>>(GameEngine::SystemLoadingMusic);
    registry.runSystems();
    return 0;
}
