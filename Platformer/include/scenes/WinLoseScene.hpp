/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** WinLoseScene
*/

#ifndef WINLOSESCENE_HPP_
#define WINLOSESCENE_HPP_
#include "utils/IScene.hpp"
#include "Platformer.hpp"

class WinLoseScene : public GameEngine::IScene
{
  public:
    WinLoseScene(GameState &state) : _state(state){};
    ~WinLoseScene() = default;
    void load() override;
    void unload() override;

  private:
    GameState &_state;
};

#endif /* !WINLOSESCENE_HPP_ */