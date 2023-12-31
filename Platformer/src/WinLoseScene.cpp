/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** WinLoseScene
*/

#include "scenes/WinLoseScene.hpp"
#include <iostream>

void WinLoseScene::load()
{
    GameEngine::Entity background =
        _gameEngine.prefabManager.createEntityFromPrefab("background", _gameEngine.registry);
    GameEngine::Entity textCamera = _gameEngine.prefabManager.createEntityFromPrefab("UICamera", _gameEngine.registry);
    GameEngine::Entity cam = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
    GameEngine::Entity buttonQuit =
        _gameEngine.prefabManager.createEntityFromPrefab("buttonQuit", _gameEngine.registry);
    GameEngine::Entity buttonRestart =
        _gameEngine.prefabManager.createEntityFromPrefab("buttonRestart", _gameEngine.registry);
    GameEngine::Entity title = _gameEngine.registry.spawnEntity();
    _entities.push_back(background);
    _entities.push_back(cam);
    _entities.push_back(title);
    _entities.push_back(buttonQuit);
    _entities.push_back(textCamera);
    _entities.push_back(buttonRestart);
    GameEngine::TextComponent textTitle{
        "default", "Platformer/assets/8-bit fortress.ttf", 90, GameEngine::Text(), true, 50};
    if (_state == GameState::win)
        textTitle.str = "Win";
    else
        textTitle.str = "Game Over";
    textTitle.text.load(textTitle.str,
        _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf").getFont(), textTitle.size);
    textTitle.text.setPosition(GameEngine::Vector2<float>{(1920 - textTitle.text.getLocalBounds().width) / 2,
        (1080 - textTitle.text.getLocalBounds().height) / 3 + 1000});
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(title, textTitle);
    _gameEngine.registry.addComponent<GameEngine::PressableComponent>(buttonRestart,
        GameEngine::PressableComponent{GameEngine::Recti(0, 0, 48, 16), GameEngine::Recti(0, 0, 48, 16),
            GameEngine::Recti(48, 0, 48, 16), GameEngine::Recti(96, 0, 48, 16), GameEngine::defaultState, [this]() {
                this->_gameEngine.sceneManager.unloadScene();
                this->_state = GameState::Restart;
                this->_gameEngine.sceneManager.loadScene("Game");
            }});
    _gameEngine.registry.addComponent<GameEngine::PressableComponent>(buttonQuit,
        GameEngine::PressableComponent{GameEngine::Recti(0, 0, 48, 16), GameEngine::Recti(0, 0, 48, 16),
            GameEngine::Recti(48, 0, 48, 16), GameEngine::Recti(96, 0, 48, 16), GameEngine::defaultState, [this]() {
                this->_gameEngine.sceneManager.unloadScene();
                this->_isOpen = false;
                this->_gameEngine.eventManager.publish<bool &>(
                    static_cast<GameEngine::EventType>(GameEngine::Event::QuitEvent), _isOpen);
            }});
    auto &tfBRest = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[buttonRestart];
    auto &tfBQ = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[buttonQuit];
    auto &txBRest = _gameEngine.registry.getComponent<GameEngine::TextComponent>()[buttonRestart];
    auto &txBQ = _gameEngine.registry.getComponent<GameEngine::TextComponent>()[buttonQuit];
    if (tfBRest && txBRest)
        txBRest->text.setPosition(GameEngine::Vector2{tfBRest->position.x + 733, tfBRest->position.y + 1590});
    if (tfBQ && txBQ)
        txBQ->text.setPosition(GameEngine::Vector2{tfBQ->position.x + 755, tfBQ->position.y + 1705});
    std::cout << "Loading WinLoseScene" << std::endl;
}

void WinLoseScene::addEntityToUnload(GameEngine::Entity) {}

void WinLoseScene::unload()
{
    for (std::size_t i = 0; i < _entities.size(); i++)
        _gameEngine.registry.killEntity(_entities[i]);
    _entities.clear();
    std::cout << "Unloading WinLoseScene" << std::endl;
}

void WinLoseScene::update() {}
