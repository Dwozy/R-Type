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
#include <nlohmann/json.hpp>

namespace GameEngine
{
    class PrefabManager
    {
      public:
        PrefabManager() = default;
        ~PrefabManager() = default;
        void loadPrefabFromFile(const std::string &filename);

      protected:
      private:
        std::unordered_map<std::string, nlohmann::json> _prefabsJson;
    };
} // namespace GameEngine

#endif /* !PREFABMANAGER_HPP_ */
