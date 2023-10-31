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
        _gameEngine.prefabManager.loadPrefabFromFile("./Platformer/config/Player.json");
        GameEngine::Entity player = _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry);
    }
    if (_state == GameState::Pause) {
        std::cout << "resume game" << std::endl;
    }
}

void GameScene::unload()
{
    std::cout << "unloading GameScene" << std::endl;
}
