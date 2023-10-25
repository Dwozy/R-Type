/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** PrefabManager
*/

#ifndef PREFABMANAGER_HPP_
#define PREFABMANAGER_HPP_

#include <string>
#include <unordered_map>
#include <typeindex>
#include <functional>
#include <nlohmann/json.hpp>
#include "Entity.hpp"
#include "Registry.hpp"
#include "AssetManager.hpp"

using json = nlohmann::json;

namespace GameEngine
{
    class PrefabManager
    {
      public:
        PrefabManager(AssetManager &assetManager);
        ~PrefabManager() = default;
        void loadPrefabFromFile(const std::string &filename);
        Entity createEntityFromPrefab(const std::string &prefabName, Registry &registry);
        Entity createEntityFromPrefab(const std::string &prefabName, Registry &registry, size_t id);

      protected:
      private:
        std::reference_wrapper<AssetManager> _assetManager;
        std::unordered_map<std::string, std::unordered_map<std::type_index, std::any>> _prefabs;
        std::unordered_map<std::string, std::function<std::pair<std::type_index, std::any>(json)>> _componentConverters;
        std::unordered_map<std::type_index, std::function<void(Registry &registry, const std::any &, Entity)>>
            _componentAdders;
    };
} // namespace GameEngine

#endif /* !PREFABMANAGER_HPP_ */
