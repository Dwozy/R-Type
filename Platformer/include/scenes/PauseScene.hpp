/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** PauseScene
*/

#ifndef PAUSESCENE_HPP_
#define PAUSESCENE_HPP_
#include "utils/IScene.hpp"
#include "GameEngine.hpp"
#include "Platformer.hpp"

/// @brief PauseScene class that herites from the IScene interface
class PauseScene : public GameEngine::IScene
{
  public:
    /// @brief constructor
    /// @param gameEngine the GameEngine instance
    /// @param state state of game
    /// @param isOpen boolean indicating if the window is open
    PauseScene(GameEngine::GameEngine &gameEngine, GameState &state, bool &isOpen)
        : _gameEngine(gameEngine), _state(state), _isOpen(isOpen)
    {};
    /// @brief default construtor
    ~PauseScene() = default;
    /// @brief load the scene
    void load() override;
    /// @brief unload the scene
    void unload() override;
    /// @brief add entiries that have to be unloaded
    /// @param entity entity that will be unloaded
    void addEntityToUnload(GameEngine::Entity entity) override;
    /// @brief update the scene
    void update() override;

  private:
    GameState &_state;
    bool &_isOpen;
    GameEngine::GameEngine &_gameEngine;
    std::vector<GameEngine::Entity> _entities;
};

#endif /* !PAUSESCENE_HPP_ */
