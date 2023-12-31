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

class MainMenuScene : public GameEngine::IScene
{
  public:
    MainMenuScene(GameEngine::GameEngine &gameEngine, GameState &state) : _gameEngine(gameEngine), _state(state)
    {};
    ~MainMenuScene() = default;
    void load() override;
    void unload() override;
    void addEntityToUnload(GameEngine::Entity entity) override;
    void update() override;

  private:
    std::vector<GameEngine::Entity> _entities;
    GameEngine::GameEngine &_gameEngine;
    GameState &_state;
};

#endif /* !MAINMENUSCENE_HPP_ */
