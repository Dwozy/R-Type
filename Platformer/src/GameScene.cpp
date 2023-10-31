/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GameScene
*/

#include "scenes/GameScene.hpp"
#include <iostream>

void GameScene::load()
{
    std::cout << "Loading GameScene" << std::endl;
    if (_state == GameState::Mainmenu || _state == GameState::Restart) {
        std::cout << "create game from start" << std::endl;
        GameEngine::Entity player = _gameEngine.registry.spawnEntity();
        _gameEngine.registry.addComponent(player, GameEngine::TransformComponent{GameEngine::Vector2<float>{960.0f, 540.0f}, GameEngine::Vector2<float>{0.0f, 0.0f},});

        GameEngine::Texture texture;
        GameEngine::Sprite sprite;
        texture.load("Platformer/assets/pata_pata.gif", GameEngine::Rect<int>(0, 0, 32, 16));
        sprite.load(texture);
        _gameEngine.registry.addComponent(player, GameEngine::TextureComponent{"Platformer/assets/pata_pata.gif", sprite, false, std::vector<GameEngine::Rect<int>>{GameEngine::Rect<int>(0, 0, 32, 16)}, true, 0, 0, 1});
    }
    if (_state == GameState::Pause) {
        std::cout << "resume game" << std::endl;
    }
}

void GameScene::unload()
{
    std::cout << "unloading GameScene" << std::endl;
}
