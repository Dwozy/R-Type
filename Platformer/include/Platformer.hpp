/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** Platformer
*/

#ifndef PLATFORMER_HPP_
#define PLATFORMER_HPP_
#include "GameEngine.hpp"


/// @brief enum of all the game state
enum class GameState { Mainmenu, Pause, Game, win, Lose, Restart, Finnished };

/// @brief class of the game
class Platformer
{
  public:
    Platformer();
    ~Platformer() = default;
    /// @brief set all the game Components
    void setGameEngineComponent();
    /// @brief set all the system
    void setGameEngineSystem();
    /// @brief set all the game scene
    void setGameEngineScene();
    /// @brief set the gameEngine
    void setGameEngine();
    /// @brief handle when the scene has to be changed
    void handleSceneChange();
    /// @brief handle when the player jump
    void handlePlayerjump();
    /// @brief set all Font of the game
    void setGameEngineFont();
    /// @brief set all the Prefab of the game
    void setGameEnginePrefab();
    /// @brief game loop of the game
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
