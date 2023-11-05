/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** MainMenuScene
*/

#include "scenes/MainMenuScene.hpp"
#include <iostream>

void MainMenuScene::load()
{
    GameEngine::Entity background =
        _gameEngine.prefabManager.createEntityFromPrefab("background", _gameEngine.registry);
    GameEngine::Entity textCamera = _gameEngine.prefabManager.createEntityFromPrefab("UICamera", _gameEngine.registry);
    GameEngine::Entity cam = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
    GameEngine::Entity title = _gameEngine.registry.spawnEntity();
    GameEngine::Entity start = _gameEngine.registry.spawnEntity();
    _entities.push_back(background);
    _entities.push_back(cam);
    _entities.push_back(title);
    _entities.push_back(textCamera);
    _entities.push_back(start);
    GameEngine::TextComponent textTitle{"SCP 745 adventures", "Platformer/assets/8-bit fortress.ttf", 100, GameEngine::Text(), true, 50};
    GameEngine::TextComponent textsubTitle{"press escap to start", "Platformer/assets/8-bit fortress.ttf", 75, GameEngine::Text(), true, 50};
    textTitle.text.load(textTitle.str, _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf").getFont(), textTitle.size);
    textsubTitle.text.load(textsubTitle.str, _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf").getFont(), textsubTitle.size);
    textTitle.text.setPosition(GameEngine::Vector2<float>{(1920 - textTitle.text.getLocalBounds().width) / 2, (1080 - textTitle.text.getLocalBounds().height) / 3 + 1000 });
    textsubTitle.text.setPosition(GameEngine::Vector2<float>{(1920 - textsubTitle.text.getLocalBounds().width) / 2, (1080 - textsubTitle.text.getLocalBounds().height) / 1.5f + 1000});
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(title, textTitle);
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(start, textsubTitle);
    std::cout << "Loading MainMenuScene" << std::endl;
}

void MainMenuScene::unload()
{
    for (std::size_t i = 0; i < _entities.size(); i++)
        _gameEngine.registry.killEntity(_entities[i]);
    _entities.clear();
    std::cout << "Unloading MainMenuScene" << std::endl;
}

void MainMenuScene::update() {}
