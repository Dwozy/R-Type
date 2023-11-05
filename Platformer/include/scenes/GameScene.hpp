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
#include "components/HealthComponent.hpp"

class GameScene : public GameEngine::IScene
{
  public:
    GameScene(GameEngine::GameEngine &gameEngine, GameState &state, size_t &id, bool &jumping)
        : _gameEngine(gameEngine), _state(state), _id(id), _jumping(jumping), _mapLoader(gameEngine, _entities),
          lastTime(std::chrono::steady_clock::now())
    {
        _isLoaded = true;
    };
    ~GameScene() = default;
    void load() override;
    void unload() override;
    void addEntityToUnload(GameEngine::Entity entity) override;
    void update() override;
    void playerCollisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
        SparseArray<GameEngine::TransformComponent> &transforms, SparseArray<GameEngine::GravityComponent> &gravity,
        SparseArray<GameEngine::HealthComponent> &health);
    void endOfLevelCollsionCallback(const std::size_t &entityId,
        SparseArray<GameEngine::CollisionComponent> &collisions,
        SparseArray<GameEngine::TransformComponent> &transforms);

  private:
    SparseArray<GameEngine::CameraComponent> camcpy;
    SparseArray<GameEngine::CollisionComponent> collscpy;
    SparseArray<GameEngine::ControllableComponent> ctrlscpy;
    SparseArray<GameEngine::GravityComponent> gravscpy;
    SparseArray<GameEngine::PressableComponent> presscpy;
    SparseArray<GameEngine::TextComponent> textscpy;
    SparseArray<GameEngine::TextureComponent> texturescpy;
    SparseArray<GameEngine::TransformComponent> trscpy;
    std::vector<GameEngine::Entity> _entities;
    std::vector<GameEngine::Entity> _heartEntities;
    GameEngine::GameEngine &_gameEngine;
    GameState &_state;
    size_t &_id;
    MapLoader _mapLoader;
    bool &_jumping;
    bool _isLoaded;
    std::chrono::steady_clock::time_point lastTime;
};

#endif /* !GAMESCENE_HPP_ */
