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

class WinLoseScene : public GameEngine::IScene
{
  public:
    WinLoseScene(GameEngine::GameEngine &gameEngine, bool &win, bool &isOpen)
        : _gameEngine(gameEngine), _win(win), _isOpen(isOpen)
    {
        _font.load("Platformer/assets/8-bit fortress.ttf");
    };
    ~WinLoseScene() = default;
    void load() override;
    void unload() override;
    void update() override;

  private:
    GameEngine::Font _font;
    bool &_win;
    bool &_isOpen;
    GameEngine::GameEngine &_gameEngine;
    std::vector<GameEngine::Entity> _entities;
};

#endif /* !WINLOSESCENE_HPP_ */
