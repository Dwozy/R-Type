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

    PrefabManager::PrefabManager(AssetManager &assetManager) : _assetManager(assetManager)
    {
        _componentConverters["TransformComponent"] = [](json json) {
            return std::pair(std::type_index(typeid(TransformComponent)), json.get<TransformComponent>());
        };
        _componentConverters["ControllableComponent"] = [](json json) {
            return std::pair(std::type_index(typeid(ControllableComponent)), json.get<ControllableComponent>());
        };
        _componentConverters["TextureComponent"] = [](json json) {
            return std::pair(std::type_index(typeid(TextureComponent)), json.get<TextureComponent>());
        };
        _componentConverters["CollisionComponent"] = [](json json) {
            return std::pair(std::type_index(typeid(CollisionComponent)), json.get<CollisionComponent>());
        };

        _componentAdders[typeid(TransformComponent)] = [](Registry &registry, const std::any &component,
                                                           Entity entity) {
            return registry.addComponent(entity, std::any_cast<TransformComponent>(component));
        };
        _componentAdders[typeid(TextureComponent)] = [](Registry &registry, const std::any &component, Entity entity) {
            registry.addComponent(entity, std::any_cast<TextureComponent>(component));
        };
        _componentAdders[typeid(CollisionComponent)] = [](Registry &registry, const std::any &component,
                                                           Entity entity) {
            return registry.addComponent(entity, std::any_cast<CollisionComponent>(component));
        };
        _componentAdders[typeid(ControllableComponent)] = [](Registry &registry, const std::any &component,
                                                              Entity entity) {
            return registry.addComponent(entity, std::any_cast<ControllableComponent>(component));
        };
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

        for (auto &component : json["components"]) {
            if (!component.contains("type") || !_componentConverters.contains(component["type"].get<std::string>()))
                throw Error::InvalidPrefabFileError();
            _prefabs[name].emplace(_componentConverters[component["type"].get<std::string>()](component.at("value")));
        }
    }

    Entity PrefabManager::createEntityFromPrefab(const std::string &prefabName, Registry &registry)
    {
        auto entity = registry.spawnEntity();

        for (const auto &prefab : _prefabs.at(prefabName)) {
            _componentAdders.at(prefab.first)(registry, prefab.second, entity);
            if (prefab.first == typeid(TextureComponent)) {
                auto &texture = registry.getComponent<TextureComponent>()[entity];
                texture->sprite.load(_assetManager.get().getTexture(texture->path));
            }
        }
        return entity;
    }

    Entity PrefabManager::createEntityFromPrefab(const std::string &prefabName, Registry &registry, size_t id)
    {
        auto entity = registry.spawnEntity(id);

        for (const auto &prefab : _prefabs.at(prefabName)) {
            _componentAdders.at(prefab.first)(registry, prefab.second, entity);
            if (prefab.first == typeid(TextureComponent)) {
                auto &texture = registry.getComponent<TextureComponent>()[entity];
                texture->sprite.load(_assetManager.get().getTexture(texture->path));
            }
        }
        return entity;
    }
} // namespace GameEngine
