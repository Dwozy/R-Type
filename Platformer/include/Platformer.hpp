/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** Platformer
*/

#ifndef PLATFORMER_HPP_
#define PLATFORMER_HPP_
#include "GameEngine.hpp"


enum class GameState {
    Mainmenu,
    Pause,
    Game,
    win,
    Lose,
    Restart
};

class Platformer {
    public:
        Platformer();
        ~Platformer();
        void setGameEngineComponent();
        void setGameEngineCallback();
        void setGameEngineSystem();
        void setGameEngineScene();
        void setGameEngine();
        void handleScreenChange();
        void gameLoop();
    private:
        GameState _state;
        GameEngine::GameEngine _gameEngine;
};

#endif /* !PLATFORMER_HPP_ */
