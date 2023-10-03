/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CreatePlayer
*/

#include "GameManager.hpp"

void CreatePlayer(GameManager &GameManager)
{
    GameEngine::Entity entity = GameManager.gameEngine.registry.spawnEntity();
    GameEngine::PositionComponent pos = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::VelocityComponent vel = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::ControllableComponent con = {
        GameEngine::Input::Keyboard::Z,
        GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S,
        GameEngine::Input::Keyboard::D,
        100.0f
    };
    GameManager.gameEngine.registry.addComponent<GameEngine::PositionComponent>(entity, pos);
    GameManager.gameEngine.registry.addComponent<GameEngine::VelocityComponent>(entity, vel);
    GameManager.gameEngine.registry.addComponent<GameEngine::ControllableComponent>(entity, con);

    GameEngine::Texture texture;
    texture.load("image.png", GameEngine::Rect<int>(0, 0, 32, 16));
    GameEngine::Sprite sprite;
    sprite.load(texture);
    GameManager.gameEngine.registry.addComponent<GameEngine::TextureComponent>(entity, GameEngine::TextureComponent{ texture, sprite, true, 1 });
}


