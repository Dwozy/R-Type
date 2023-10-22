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

    PrefabManager::PrefabManager()
    {
        _componentFunctions["TransformComponent"] = [](json json){return std::pair(std::type_index(typeid(TransformComponent)), json.at("value").get<TransformComponent>());};
        _componentFunctions["ControllableComponent"] = [](json json){return std::pair(std::type_index(typeid(ControllableComponent)), json.at("value").get<ControllableComponent>());};
        _componentFunctions["TextureComponent"] = [](json json){return std::pair(std::type_index(typeid(TextureComponent)), json.at("value").get<TextureComponent>());};
        _componentFunctions["CollisionComponent"] = [](json json){return std::pair(std::type_index(typeid(CollisionComponent)), json.at("value").get<CollisionComponent>());};
    }

    void PrefabManager::loadPrefabFromFile(const std::string &filename)
    {
        std::ifstream infile(filename);

        if (!infile)
            throw Error::InvalidPrefabFileError(); // No file or invalid file

        json json = json::parse(infile);
        if (!json.contains("name"))
            throw Error::InvalidPrefabFileError();
        if (!json.contains("components"))
            throw Error::InvalidPrefabFileError();
        std::string name(json["name"].get<std::string>());
        if (_prefabs.contains(name))
            throw Error::PrefabNameAlreadyUsedError();

        for (auto &component: json["component"]) {
            if (!component.contains("type") || !_componentFunctions.contains(json["type"].get<std::string>()))
                throw Error::InvalidPrefabFileError();
            _prefabs[name].emplace(_componentFunctions[json["type"].get<std::string>()](json.at("value")));
        }
    }
} // namespace GameEngine
