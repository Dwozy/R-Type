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
    GameEngine::Entity cam = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
    GameEngine::Entity title = _gameEngine.registry.spawnEntity();
    GameEngine::Entity start = _gameEngine.registry.spawnEntity();
    _entities.push_back(background);
    _entities.push_back(cam);
    _entities.push_back(title);
    _entities.push_back(start);
    GameEngine::FontComponent fontTitle{"Platformer/assets/8-bit fortress.ttf", _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf")};
    GameEngine::TextComponent textTitle{"SCP 745 adventures", 25, GameEngine::Text(), true, 50};
    GameEngine::FontComponent fontsubtitle{"Platformer/assets/8-bit fortress.ttf", _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf")};
    GameEngine::TextComponent textsubTitle{"press escap to start", 17, GameEngine::Text(), true, 50};
    textTitle.text.load(textTitle.str, _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf").getFont(), textTitle.size);
    textsubTitle.text.load(textsubTitle.str, _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf").getFont(), textsubTitle.size);
    textTitle.text.setPosition(GameEngine::Vector2<float>{22, 75});
    textsubTitle.text.setPosition(GameEngine::Vector2<float>{65, 150});
    _gameEngine.registry.addComponent<GameEngine::FontComponent>(title, fontTitle);
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(title, textTitle);
    _gameEngine.registry.addComponent<GameEngine::FontComponent>(start, fontsubtitle);
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
