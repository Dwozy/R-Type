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

class PauseScene : public GameEngine::IScene
{
  public:
    PauseScene(GameEngine::GameEngine &gameEngine, GameState &state, bool &isOpen)
        : _gameEngine(gameEngine), _state(state), _isOpen(isOpen)
    {};
    ~PauseScene() = default;
    void load() override;
    void unload() override;
    void addEntityToUnload(GameEngine::Entity entity) override;
    void update() override;

  private:
    GameState &_state;
    bool &_isOpen;
    GameEngine::GameEngine &_gameEngine;
    std::vector<GameEngine::Entity> _entities;
};

#endif /* !PAUSESCENE_HPP_ */
