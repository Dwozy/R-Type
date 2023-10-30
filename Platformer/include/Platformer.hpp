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
    Pause,
    Game,
    win,
    Lose
};

class Platformer {
    public:
        Platformer();
        ~Platformer();
        void setGameEngineComponent();
        void setGameEngineCallback();
        void setGameEngineSystem();
        void setGameEngine();
        void gameLoop();
    private:
        GameEngine::GameEngine _gameEngine;
};

#endif /* !PLATFORMER_HPP_ */
