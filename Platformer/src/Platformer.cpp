/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** Platformer
*/

#include "Platformer.hpp"

Platformer::Platformer()
{
    // spawn l'entity camera me fait quelque probleme avec l'entity player
    // GameEngine::Entity camera = _gameEngine.registry.spawnEntity();
    // GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 200.0f, 200.0f)}};
    // auto &refCamera = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);
    _state = GameState::Mainmenu;
    setGameEngine();
    gameLoop();
}

void Platformer::handlePlayerjump()
{
    static bool canJump = true;
    if (_state != GameState::Game)
        return;
    auto &grav = _gameEngine.registry.getComponent<GameEngine::GravityComponent>();
    if (!grav[_id].has_value())
        return;
    if (GameEngine::InputManager::isKeyPressed(GameEngine::Input::Keyboard::Space) && canJump) {
        grav[_id]->cumulatedGVelocity.y = -100;
        canJump = false;
    }
    if (GameEngine::InputManager::isKeyReleased(GameEngine::Input::Keyboard::Space))
        canJump = true;
}

void Platformer::handlePlayerMove()
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
        handleScreenChange();
        handlePlayerjump();
        handlePlayerMove();
        _gameEngine.eventManager.publish<bool &>(GameEngine::Event::WindowIsOpen, isOpen);
    }
}
