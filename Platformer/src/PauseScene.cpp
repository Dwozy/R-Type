/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** PauseScene
*/

#include "scenes/PauseScene.hpp"
#include <iostream>

void PauseScene::load()
{
    GameEngine::Entity background =
        _gameEngine.prefabManager.createEntityFromPrefab("background", _gameEngine.registry);
    GameEngine::Entity textCamera = _gameEngine.prefabManager.createEntityFromPrefab("UICamera", _gameEngine.registry);
    GameEngine::Entity cam = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
    GameEngine::Entity buttonResume =
        _gameEngine.prefabManager.createEntityFromPrefab("buttonResume", _gameEngine.registry);
    GameEngine::Entity buttonQuit =
        _gameEngine.prefabManager.createEntityFromPrefab("buttonQuit", _gameEngine.registry);
    GameEngine::Entity buttonRestart =
        _gameEngine.prefabManager.createEntityFromPrefab("buttonRestart", _gameEngine.registry);
    GameEngine::Entity title = _gameEngine.registry.spawnEntity();
    _entities.push_back(background);
    _entities.push_back(cam);
    _entities.push_back(title);
    _entities.push_back(buttonResume);
    _entities.push_back(buttonQuit);
    _entities.push_back(buttonRestart);
    _entities.push_back(textCamera);
    GameEngine::TextComponent textTitle{
        "Pause", "Platformer/assets/8-bit fortress.ttf", 80, GameEngine::Text(), true, 50};
    textTitle.text.load(textTitle.str,
        _gameEngine.assetManager.getFont("Platformer/assets/8-bit fortress.ttf").getFont(), textTitle.size);
    textTitle.text.setPosition(GameEngine::Vector2<float>{(1920 - textTitle.text.getLocalBounds().width) / 2,
        (1080 - textTitle.text.getLocalBounds().height) / 3 + 1000});
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(title, textTitle);
    _gameEngine.registry.addComponent<GameEngine::PressableComponent>(buttonResume,
        GameEngine::PressableComponent{GameEngine::Recti(0, 0, 48, 16), GameEngine::Recti(0, 0, 48, 16),
            GameEngine::Recti(48, 0, 48, 16), GameEngine::Recti(96, 0, 48, 16), GameEngine::defaultState, [this]() {
                this->_gameEngine.sceneManager.unloadScene();
                this->_gameEngine.sceneManager.loadScene("Game");
                this->_state = GameState::Game;
            }});
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
    auto &tfBRes = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[buttonResume];
    auto &tfBRest = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[buttonRestart];
    auto &tfBQ = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[buttonQuit];
    auto &txBRes = _gameEngine.registry.getComponent<GameEngine::TextComponent>()[buttonResume];
    auto &txBRest = _gameEngine.registry.getComponent<GameEngine::TextComponent>()[buttonRestart];
    auto &txBQ = _gameEngine.registry.getComponent<GameEngine::TextComponent>()[buttonQuit];
    if (tfBRes && txBRes)
        txBRes->text.setPosition(GameEngine::Vector2{tfBRes->position.x + 735, tfBRes->position.y + 1480});
    if (tfBRest && txBRest)
        txBRest->text.setPosition(GameEngine::Vector2{tfBRest->position.x + 733, tfBRest->position.y + 1590});
    if (tfBQ && txBQ)
        txBQ->text.setPosition(GameEngine::Vector2{tfBQ->position.x + 755, tfBQ->position.y + 1705});
    std::cout << "Loading PauseScene" << std::endl;
}

void PauseScene::unload()
{
    for (std::size_t i = 0; i < _entities.size(); i++)
        _gameEngine.registry.killEntity(_entities[i]);
    _entities.clear();
    std::cout << "Unloading PauseScene" << std::endl;
}

void PauseScene::addEntityToUnload(GameEngine::Entity) {}

void PauseScene::update() {}
