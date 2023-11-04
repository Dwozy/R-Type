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
    MapLoader(GameEngine::GameEngine &engine) : _engine(engine){};
    ~MapLoader() = default;
    void loadMap(const std::string &path, GameEngine::Vector2<float> const &position, float blockSize);

  protected:
  private:
    GameEngine::GameEngine &_engine;
};

void BlockcollisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms, SparseArray<GameEngine::GravityComponent> &gravity);

#endif /* !MAPLOADER_HPP_ */
