/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
#define GAMESCENE_HPP_
#include "utils/IScene.hpp"
#include "GameEngine.hpp"
#include "Platformer.hpp"
#include "MapLoader.hpp"

class GameScene : public GameEngine::IScene
{
  public:
    GameScene(GameEngine::GameEngine &gameEngine, GameState &state, size_t &id)
        : _gameEngine(gameEngine), _state(state), _id(id), _mapLoader(gameEngine){};
    ~GameScene() = default;
    void load() override;
    void unload() override;

  private:
    GameEngine::GameEngine &_gameEngine;
    GameState &_state;
    size_t &_id;
    MapLoader _mapLoader;
};

#endif /* !GAMESCENE_HPP_ */
