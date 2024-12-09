/*
** EPITECH PROJECT, 2023
** R-Type perso
** File description:
** MapLoader
*/

#ifndef MAPLOADER_HPP_
#define MAPLOADER_HPP_
#include "GameEngine.hpp"

/// @brief class that loads maps
class MapLoader
{
  public:
    /// @brief constructor
    /// @param engine the gameEngine
    /// @param entities vector of entities
    MapLoader(GameEngine::GameEngine &engine, std::vector<GameEngine::Entity> &entities)
        : _engine(engine), _entities(entities){};
    /// @brief  default destructor
    ~MapLoader() = default;
    /// @brief load the map of the game
    /// @param path the path to the map file
    /// @param position the starting position of the map
    /// @param blockSize the size of a block
    void loadMap(const std::string &path, GameEngine::Vector2<float> const &position, float blockSize);

  protected:
  private:
    GameEngine::GameEngine &_engine;
    std::vector<GameEngine::Entity> &_entities;
};

/// @brief callback function for the collision that prevents entities from falling
/// @param entityId id of the entity that hold the collision
/// @param collisions SparseArray that contain all the collision components attached to a entity
/// @param transforms SparseArray that contain all the transform components attached to a entity
/// @param gravity SparseArray that contain all the gravity components attached to a entity
void standardGravityCollisionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms,
    SparseArray<GameEngine::GravityComponent> &gravity);
/// @brief callback function for the collision that make entities change direction
/// @param entityId id of the entity that hold the collision
/// @param collisions SparseArray that contain all the collision components attached to a entity
/// @param transforms SparseArray that contain all the transform components attached to a entity
/// @param gravity SparseArray that contain all the gravity components attached to a entity
/// @param textures SpaceArray that contain all the texture components attached to a entity
void changeDirGravityCollisionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms,
    SparseArray<GameEngine::GravityComponent> &gravity, SparseArray<GameEngine::TextureComponent> &textures);

#endif /* !MAPLOADER_HPP_ */
