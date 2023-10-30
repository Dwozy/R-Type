/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** Platformer
*/

#include "Platformer.hpp"

Platformer::Platformer()
{
    setGameEngine();
    // _gameEngine.sceneManager.registerScene("Game", std::make_unique<GameScene>());
    // _gameEngine.sceneManager.loadScene("Game");
    gameLoop();
}

Platformer::~Platformer()
{
}

void Platformer::gameLoop()
{
    bool isOpen = false;
    GameEngine::PollEventStruct event;

    _gameEngine.eventManager.publish<bool &>(GameEngine::Event::WindowIsOpen, isOpen);
    while (isOpen) {
        _gameEngine.deltaTime.update();
        _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(GameEngine::Event::PollEvent, event);
        while (event.isEvent) {
            _gameEngine.eventManager.publish<GameEngine::SEvent &>(GameEngine::Event::WindowCloseEvent, event.event);
            _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(GameEngine::Event::PollEvent, event);
        }
        _gameEngine.registry.runSystems();
        _gameEngine.eventManager.publish<bool &>(GameEngine::Event::WindowIsOpen, isOpen);
    }
}
