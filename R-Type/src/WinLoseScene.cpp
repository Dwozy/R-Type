/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** WinLoseScene
*/

#include "WinLoseScene.hpp"
#include <iostream>

void WinLoseScene::load()
{
    GameEngine::Entity cam = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
    GameEngine::Entity buttonQuit =
        _gameEngine.prefabManager.createEntityFromPrefab("button_quit", _gameEngine.registry);
    GameEngine::Entity title = _gameEngine.registry.spawnEntity();
    _entities.push_back(cam);
    _entities.push_back(title);
    _entities.push_back(buttonQuit);
    GameEngine::FontComponent fontTitle{"R-Type/fonts/Valoon.ttf", _font};
    GameEngine::TextComponent textTitle{"default", 25, GameEngine::Text(), true, 50};
    if (_win)
        textTitle.str = "Win";
    else
        textTitle.str = "Game Over";
    textTitle.text.load(textTitle.str, _font.getFont(), textTitle.size);
    textTitle.text.setPosition(GameEngine::Vector2<float>{50, 50});
    _gameEngine.registry.addComponent<GameEngine::FontComponent>(title, fontTitle);
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(title, textTitle);
    _gameEngine.registry.addComponent<GameEngine::PressableComponent>(buttonQuit,
        GameEngine::PressableComponent{GameEngine::Recti(0, 0, 48, 16), GameEngine::Recti(0, 0, 48, 16),
            GameEngine::Recti(48, 0, 48, 16), GameEngine::Recti(96, 0, 48, 16), GameEngine::defaultState, [this]() {
                this->_gameEngine.sceneManager.unloadScene();
                this->_isOpen = false;
                this->_gameEngine.eventManager.publish<bool &>(
                    static_cast<GameEngine::EventType>(GameEngine::Event::QuitEvent), _isOpen);
            }});
}

void WinLoseScene::unload()
{
    for (std::size_t i = 0; i < _entities.size(); i++)
        _gameEngine.registry.killEntity(_entities[i]);
    _entities.clear();
    std::cout << "Unloading WinLoseScene" << std::endl;
}

void WinLoseScene::update() {}
