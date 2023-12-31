/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** Platformer
*/

#ifndef PLATFORMER_HPP_
#define PLATFORMER_HPP_
#include "GameEngine.hpp"

enum class GameState { Mainmenu, Pause, Game, win, Lose, Restart, Finnished };

class Platformer
{
  public:
    Platformer();
    ~Platformer() = default;
    void setGameEngineComponent();
    void setGameEngineCallback();
    void setGameEngineSystem();
    void setGameEngineScene();
    void setGameEngine();
    void handleScreenChange();
    void handlePlayerMove();
    void handlePlayerjump();
    void setGameEngineFont();
    void setGameEnginePrefab();
    void gameLoop();

  private:
    GameState _state;
    GameEngine::GameEngine _gameEngine;
    bool isOpen;
    bool isJumping;
    std::size_t _id;
    std::size_t _score;
    std::size_t _hp;
};

#endif /* !PLATFORMER_HPP_ */
