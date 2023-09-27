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

int main()
{
    Registry registry;
    Entity entity = registry.spawnEntity();
    Entity entity2 = registry.spawnEntity();
    Entity entity3 = registry.spawnEntity();

    auto &Texture = registry.registerComponent<GameEngine::Texture>();
    auto &Sprite = registry.registerComponent<GameEngine::Sprite>();
    auto &Music = registry.registerComponent<GameEngine::Music>();
    auto &Font = registry.registerComponent<GameEngine::Font>();
    auto &Text = registry.registerComponent<GameEngine::Text>();
    sa.insert_at(entity, 5);
    sa.insert_at(10, 10);
    registry.addComponent<int>(entity, 5);
    registry.removeComponent<int>(entity);
    registry.registerComponent<float>().insert_at(entity2, 2);
    auto &array = registry.getComponent<int>();
    array.emplace_at(1, 2, 3, 4);
    registry.emplaceComponent<int>(entity3, entity2, entity4);
    registry.addComponent<int>(entity5, 10);
    return 0;
}
