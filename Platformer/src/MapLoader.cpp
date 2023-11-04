/*
** EPITECH PROJECT, 2023
** R-Type perso
** File description:
** MapLoader
*/

#include "MapLoader.hpp"
#include <fstream>
#include <sstream>

static std::unordered_map<std::string, std::string> getPrefabSymbols(std::vector<std::string> &lines,
    std::vector<std::string>::iterator &vectorIter, GameEngine::PrefabManager const &prefabManager)
{
    std::unordered_map<std::string, std::string> prefabSymbols;

    while (vectorIter != lines.end() && *vectorIter != "-") {
        std::stringstream ss(*vectorIter);
        std::string symbol;
        std::string prefab;
        ss >> symbol >> prefab;
        if (symbol.size() != 1 || symbol == "#" || symbol == "-")
            throw std::runtime_error("Invalid symbol in map: " + symbol);
        if (!prefabManager.isPrefabLoaded(prefab))
            throw std::runtime_error("Unknown prefab in map: " + prefab);
        if (prefabSymbols.contains(symbol))
            throw std::runtime_error("Duplicated symbol in map: " + symbol);
        prefabSymbols[symbol] = prefab;
        vectorIter++;
    }
    vectorIter++;
    return prefabSymbols;
}

static void createMap(std::vector<std::string> &lines, std::vector<std::string>::iterator &vectorIter,
    std::unordered_map<std::string, std::string> const &prefabSymbols, GameEngine::GameEngine &engine,
    GameEngine::Vector2<float> const &position, float blockSize, std::vector<GameEngine::Entity> &entities)
{
    auto iterCopy(vectorIter);
    size_t len = iterCopy->size();

    for (size_t i = 0; iterCopy != lines.end(); iterCopy++, i++) {
        if (iterCopy->size() != len)
            throw std::runtime_error("Invalid len of line in map: line " + std::to_string(i));
        len = iterCopy->size();
    }
    for (size_t i = 0; vectorIter != lines.end(); vectorIter++, i++) {
        size_t j = 0;
        for (auto character : *vectorIter) {
            if (character == '#') {
                j++;
                continue;
            }
            if (!prefabSymbols.contains(std::string() + character))
                throw std::runtime_error(std::string("Unknown character in map: ") + character + ",line " +
                                         std::to_string(i) + ", column " + std::to_string(j));
            auto entity = engine.prefabManager.createEntityFromPrefab(
                prefabSymbols.at(std::string() + character), engine.registry);
            entities.push_back(entity);
            auto &trf = engine.registry.getComponent<GameEngine::TransformComponent>()[entity];
            if (trf)
                trf->position = {position.x + j * blockSize, position.y + i * blockSize};
            if (prefabSymbols.at(std::string() + character) == "enemy")
                engine.registry.getComponent<GameEngine::CollisionComponent>()[entity]
                    ->addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                                    SparseArray<GameEngine::TransformComponent> &,
                                    SparseArray<GameEngine::GravityComponent> &)>,
                        GameEngine::CollisionComponent, GameEngine::TransformComponent, GameEngine::GravityComponent>(
                        engine.registry, standardGravityCollisionCallback);
            j++;
        }
    }
}

void MapLoader::loadMap(std::string const &path, GameEngine::Vector2<float> const &position, float blockSize)
{
    std::ifstream file(path);

    if (!file)
        throw std::runtime_error("MapLoader::loadMap : File not found");

    std::string line;
    std::vector<std::string> lines;

    while (std::getline(file, line))
        lines.push_back(line);

    auto iter = lines.begin();
    auto prefabSymbols = getPrefabSymbols(lines, iter, _engine.prefabManager);
    createMap(lines, iter, prefabSymbols, _engine, position, blockSize, _entities);
}
