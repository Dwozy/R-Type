/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** PrefabManager
*/

#include "utils/PrefabManager.hpp"
#include <fstream>
#include <iostream>

namespace GameEngine
{
    void PrefabManager::loadPrefabFromFile(const std::string &filename)
    {
        std::ifstream infile(filename);

        if (!infile)
            throw; // No file or invalid file

        nlohmann::json json = nlohmann::json::parse(infile);
        if (!json.contains("name"))
            throw; // Invalid prefab: missing name
        std::string name(json["name"].get<std::string>());
        if (_prefabsJson.contains(name))
            throw; // Already exists
        _prefabsJson[name] = json;
        std::cout << _prefabsJson << std::endl;
    }
} // namespace GameEngine
