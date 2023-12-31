/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** Platformer
*/

#include "Platformer.hpp"

Platformer::Platformer()
{
    _state = GameState::Mainmenu;
    isJumping = false;
    setGameEngine();
    // GameEngine::Entity musicHolder = _gameEngine.registry.spawnEntity();
    // GameEngine::MusicComponent music{"Platformer/assets/dungeon.wav", std::make_shared<GameEngine::Music>()};
    // music.music->load(music.path);
    // _gameEngine.registry.addComponent<GameEngine::MusicComponent>(musicHolder, music);
    gameLoop();
    isOpen = false;
}

void Platformer::handlePlayerjump()
{
    static bool canJump = true;
    if (_state != GameState::Game)
        return;
    auto &grav = _gameEngine.registry.getComponent<GameEngine::GravityComponent>();
    if (!grav[_id].has_value())
        return;
    if (GameEngine::InputManager::isKeyPressed(GameEngine::Input::Keyboard::Space) && canJump && !isJumping) {
        grav[_id]->cumulatedGVelocity.y = -110;
        canJump = false;
        isJumping = true;
    }
    if (GameEngine::InputManager::isKeyReleased(GameEngine::Input::Keyboard::Space))
        canJump = true;
}

void Platformer::handlePlayerMove() {}

void Platformer::gameLoop()
{
    GameEngine::PollEventStruct event;

    _gameEngine.eventManager.publish<bool &>(
        static_cast<GameEngine::EventType>(GameEngine::Event::WindowIsOpen), isOpen);
    while (isOpen) {
        _gameEngine.deltaTime.update();
        _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(
            static_cast<GameEngine::EventType>(GameEngine::Event::PollEvent), event);
        while (event.isEvent) {
            _gameEngine.eventManager.publish<GameEngine::SEvent &>(
                static_cast<GameEngine::EventType>(GameEngine::Event::WindowCloseEvent), event.event);
            _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(
                static_cast<GameEngine::EventType>(GameEngine::Event::PollEvent), event);
        }
        _gameEngine.registry.runSystems();
        handleScreenChange();
        handlePlayerjump();
        handlePlayerMove();
        _gameEngine.sceneManager.updateCurrentScene();
        _gameEngine.eventManager.publish<bool &>(
            static_cast<GameEngine::EventType>(GameEngine::Event::WindowIsOpen), isOpen);
    }
}
