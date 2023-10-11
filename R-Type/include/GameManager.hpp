/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#ifndef GAMEMANAGER_HPP_
    #define GAMEMANAGER_HPP_
    #include "GameEngine.hpp"
    #include "Ennemies.hpp"
    #include <cstddef>

class GameManager
{
    public:
        GameManager(int width = 1920, int height = 1080, std::string windowName = "default") : gameEngine(width, height, windowName) {};
        ~GameManager() = default;
        GameEngine::GameEngine gameEngine;
    private:
};

class Player
{
    public:
        Player(GameManager &GameManager,
            GameEngine::PositionComponent pos,
            GameEngine::VelocityComponent vel,
            GameEngine::ControllableComponent con) : _player(GameManager.gameEngine.registry.spawnEntity()), _pos(pos), _vel(vel), _con(con) {
                _texture.load("image.png", GameEngine::Rect<int>(0, 0, 32, 16));
                _sprite.load(_texture);
                _tex = GameEngine::TextureComponent{ _texture, _sprite, true, 1};
                GameManager.gameEngine.registry.addComponent<GameEngine::PositionComponent>(_player, _pos);
                GameManager.gameEngine.registry.addComponent<GameEngine::VelocityComponent>(_player, _vel);
                GameManager.gameEngine.registry.addComponent<GameEngine::ControllableComponent>(_player, _con);
                GameManager.gameEngine.registry.addComponent<GameEngine::TextureComponent>(_player, _tex);
        };
        ~Player() = default;
    private:
        GameEngine::Entity _player;
        GameEngine::PositionComponent _pos;
        GameEngine::VelocityComponent _vel;
        GameEngine::ControllableComponent _con;
        GameEngine::TextureComponent _tex;
        GameEngine::Texture _texture;
        GameEngine::Sprite _sprite;
};

void CreateCamera(GameManager &GameManager);
void CreatePlayer(GameManager &GameManager);
void RegisterComponent(GameManager &GameManager);
void RegisterSystems(GameManager &GameManager);
void gameLoop(GameManager &game);

#endif /* !GAMEMANAGER_HPP_ */
