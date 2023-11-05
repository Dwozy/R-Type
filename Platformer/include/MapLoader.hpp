/*
** EPITECH PROJECT, 2023
** R-Type perso
** File description:
** MapLoader
*/

#ifndef MAPLOADER_HPP_
#define MAPLOADER_HPP_
#include "GameEngine.hpp"

class MapLoader
{
  public:
    MapLoader(GameEngine::GameEngine &engine, std::vector<GameEngine::Entity> &entities)
        : _engine(engine), _entities(entities){};
    ~MapLoader() = default;
    void loadMap(const std::string &path, GameEngine::Vector2<float> const &position, float blockSize);

  protected:
  private:
    GameEngine::GameEngine &_engine;
    std::vector<GameEngine::Entity> &_entities;
};

void standardGravityCollisionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms,
    SparseArray<GameEngine::GravityComponent> &gravity);
void changeDirGravityCollisionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms,
    SparseArray<GameEngine::GravityComponent> &gravity, SparseArray<GameEngine::TextureComponent> &textures);

#endif /* !MAPLOADER_HPP_ */
