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

/// @brief GameScene class that herites from the IScene interface
class GameScene : public GameEngine::IScene
{
  public:
    /// @brief constructor
    /// @param gameEngine the GameEngine instance
    /// @param state state for the game
    /// @param id id of the player
    /// @param jumping boleans that indicate if the player is jumping
    GameScene(GameEngine::GameEngine &gameEngine, GameState &state, size_t &id, bool &jumping)
        : _gameEngine(gameEngine), _state(state), _id(id), _jumping(jumping), _mapLoader(gameEngine, _entities),
          lastTime(std::chrono::steady_clock::now())
    {
        _isLoaded = true;
    };
    /// @brief default constructor
    ~GameScene() = default;
    /// @brief load the scene
    void load() override;
    /// @brief unload the scene
    void unload() override;
    /// @brief update the scene
    void update() override;
    /// @brief add entiries that have to be unloaded
    /// @param entity entity that will be unloaded
    void addEntityToUnload(GameEngine::Entity entity) override;
    /// @brief callback function of the player collision
    /// @param entityId id of the entity that hold the collision
    /// @param collisions SparseArray that contain all the collision components attached to a entity
    /// @param transforms SparseArray that contain all the transform components attached to a entity
    /// @param gravity SparseArray that contain all the gravity components attached to a entity
    /// @param health SparseArray that contain all the health components attached to a entity
    void playerCollisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
        SparseArray<GameEngine::TransformComponent> &transforms, SparseArray<GameEngine::GravityComponent> &gravity,
        SparseArray<GameEngine::HealthComponent> &health);

    /// @brief callback function for the Player Victory
    /// @param entityId id of the entity that hold the collision
    /// @param collisions SparseArray that contain all the collision components attached to a entity
    /// @param transforms SparseArray that contain all the transform components attached to a entity
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
