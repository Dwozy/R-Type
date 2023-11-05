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
    /// @brief Class to manage prefabs
    class PrefabManager
    {
      public:
        /// @brief Contructor
        /// @param assetManager reference to the asset manager
        PrefabManager(AssetManager &assetManager);
        /// @brief Destructor
        ~PrefabManager() = default;
        /// @brief Load a prefab
        /// @param filename name of the prefab file (json file)
        void loadPrefabFromFile(const std::string &filename);
        /// @brief Create an entity from a prefab
        /// @param prefabName Name of the prefab
        /// @param registry reference to the registry
        /// @return the created entity
        Entity createEntityFromPrefab(const std::string &prefabName, Registry &registry, bool loadTexture = true, bool loadFont = true);
        /// @brief Create an entity from a prefab
        /// @param prefabName Name of the prefab
        /// @param registry reference to the registry
        /// @param id id of the entity
        /// @return the created entity
        Entity createEntityFromPrefab(
            const std::string &prefabName, Registry &registry, size_t id, bool loadTexture = true, bool loadFont = true);
        /// @brief Check if prefab is loaded
        /// @param prefabName name of the prefab
        /// @return true if the prefab is loaded, false otherwise
        bool isPrefabLoaded(const std::string &prefabName) const;

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
