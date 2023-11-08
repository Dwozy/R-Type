/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** WinLoseScene
*/

#ifndef WINLOSESCENE_HPP_
#define WINLOSESCENE_HPP_
#include "utils/IScene.hpp"
#include "GameEngine.hpp"
#include "Platformer.hpp"

/// @brief WinLoseScene class that herites from the IScene interface
class WinLoseScene : public GameEngine::IScene
{
  public:
    /// @brief constructor
    /// @param gameEngine the GameEngine instance
    /// @param state state of the scene
    /// @param isOpen boolean indicating if the window is open
    WinLoseScene(GameEngine::GameEngine &gameEngine, GameState &state, bool &isOpen)
        : _gameEngine(gameEngine), _state(state), _isOpen(isOpen)
    {};
    /// @brief default constructor
    ~WinLoseScene() = default;
    /// @brief load the scene
    void load() override;
    void addEntityToUnload(GameEngine::Entity entity) override;
    /// @brief unload the scene
    void unload() override;
    /// @brief update the scene
    void update() override;
    /// @brief add entiries that have to be unloaded
    /// @param entity entity that will be unloaded
    void addEntityToUnload(GameEngine::Entity entity) override;

  private:
    GameState &_state;
    bool &_isOpen;
    GameEngine::GameEngine &_gameEngine;
    std::vector<GameEngine::Entity> _entities;
};

#endif /* !WINLOSESCENE_HPP_ */
