/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
#define MAINMENUSCENE_HPP_
#include "utils/IScene.hpp"
#include "GameEngine.hpp"
#include "Platformer.hpp"

/// @brief MainMenuScene class that herites from the IScene interface
class MainMenuScene : public GameEngine::IScene
{
  public:
    /// @brief constructor
    /// @param gameEngine the GameEngine instance
    /// @param state the State of Game
    MainMenuScene(GameEngine::GameEngine &gameEngine, GameState &state) : _gameEngine(gameEngine), _state(state)
    {};
    /// @brief default constructor
    ~MainMenuScene() = default;
    /// @brief load the scene
    void load() override;
    /// @brief  unload the scene
    void unload() override;
    /// @brief update the scene
    void update() override;

  private:
    std::vector<GameEngine::Entity> _entities;
    GameEngine::GameEngine &_gameEngine;
    GameState &_state;
};

#endif /* !MAINMENUSCENE_HPP_ */
