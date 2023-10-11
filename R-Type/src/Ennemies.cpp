/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Ennemies
*/

#include "Ennemies.hpp"

void Ennemies::create_ennemie(size_t id, Ennemies::Name_Ennemie name)
{
    _ennemies.insert({id, _all_ennemies[name](_gameEngine)});
}

Ennemie &Ennemies::get_ennemie(size_t id)
{
    return _ennemies.find(id)->second;
}

void Ennemies::destroy_ennemie(size_t id)
{
    _ennemies.erase(id);
}

Ennemie create_Pata_Pata(GameEngine::GameEngine &gameEngine)
{
    GameEngine::Texture texture;
    GameEngine::Sprite sprite;
    texture.load("R-Type/assets/pata_pata.gif", GameEngine::Rect<int>(0, 0 , 32, 16));
    sprite.load(texture);
    Ennemie Patapata(gameEngine, GameEngine::PositionComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
    GameEngine::VelocityComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
    GameEngine::TextureAnimatedComponent{texture, sprite, true, GameEngine::Rect<int>(0, 0 , 36, 36),
    GameEngine::Rect<int>(0, 0 , 36, 36), GameEngine::Rect<int>(0, 0 , 36, 36), 0.1, GameEngine::DeltaTime(), true, 2}, texture, sprite);
    return Patapata;
};
