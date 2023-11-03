/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** ChangeScene
*/

#include "Platformer.hpp"

void Platformer::handleScreenChange()
{
    static bool changable = true;
    if (GameEngine::InputManager::isKeyPressed(GameEngine::Input::Keyboard::Escape) == true && changable == true) {
        changable = false;
        if (_state == GameState::Mainmenu) {
            _gameEngine.sceneManager.unloadScene();
            _gameEngine.sceneManager.loadScene("Game");
            _state = GameState::Game;
            return;
        }
        if (_state == GameState::Game) {
            _gameEngine.sceneManager.unloadScene();
            _gameEngine.sceneManager.loadScene("Pause");
            _state = GameState::Pause;
            return;
        }
        if (_state == GameState::Pause) {
            _gameEngine.sceneManager.unloadScene();
            _gameEngine.sceneManager.loadScene("Game");
            _state = GameState::Game;
            return;
        }
    }
    if (GameEngine::InputManager::isKeyReleased(GameEngine::Input::Keyboard::Escape) == true)
        changable = true;
}
