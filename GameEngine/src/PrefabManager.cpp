/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** PrefabManager
*/

#include "PrefabManager.hpp"
#include "utils/JsonConversion.hpp"
#include "Error.hpp"
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
            throw Error::InvalidPrefabFileError();
        if (!json.contains("components"))
            throw Error::InvalidPrefabFileError();
        std::string name(json["name"].get<std::string>());
        if (_prefabs.contains(name))
            throw Error::PrefabNameAlreadyUsedError();
        for (auto &component: json["component"]) {
            if (!component.contains("type"))
                throw Error::InvalidPrefabFileError();
        }
    }
} // namespace GameEngine
