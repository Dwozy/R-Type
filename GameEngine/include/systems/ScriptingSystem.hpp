/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** ScriptingSystem
*/

#ifndef SCRIPTINGSYSTEM_HPP_
#define SCRIPTINGSYSTEM_HPP_
#include <functional>
#include <unordered_map>
#include <sol/sol.hpp>
#include <memory>
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "components/ScriptComponent.hpp"
#include "components/TransformComponent.hpp"
#include "utils/Vector.hpp"

#include <iostream>

namespace GameEngine
{
    using ScriptingFunction = std::function<void(SparseArray<ScriptComponent> &)>;

    class ScriptingSystem
    {
      public:
        ScriptingSystem(Registry &registry);
        ~ScriptingSystem() = default;

        void operator()(SparseArray<ScriptComponent> &scripts);
        template <typename Component>
        void registerType(const std::string &componentName)
        {
            _setters.push_back([this, componentName](sol::state &lua) {
                // engine.new_usertype<Component>("componentName");
                lua.set_function("get_" + componentName + "_component", [this]() {
                    auto &sArray = _registry.getComponent<Component>();
                    return &sArray._data;
                });
                lua.set_function("get_" + componentName + "_component_id", [this](std::size_t index) {
                    auto &sArray = _registry.getComponent<Component>();
                    return std::ref(sArray[index]);
                });
            });
        };

      private:
        void _setLua(sol::state &lua)
        {
            // auto engine = lua["engine"].get_or_create<sol::table>();
            lua.new_usertype<Vector2<float>>("vector2f", "x", &Vector2<float>::x, "y", &Vector2<float>::y);
            lua.new_usertype<TransformComponent>(
                "transform", "position", &TransformComponent::position/*, "velocity", &TransformComponent::velocity*/);
            lua.set_function("get_position", [this](std::size_t idx) {
                auto &tsfs = _registry.getComponent<TransformComponent>();
                std::optional<std::shared_ptr<Vector2<float>>> pos;
                if (tsfs[idx].has_value()) {
                    std::shared_ptr<Vector2<float>> ptr(&tsfs[idx].value().position, [](void *){});
                    pos = ptr;
                }
                return pos;
            });
            for (auto &setter : _setters) {
                setter(lua);
            };
        };

        Registry &_registry;
        std::unordered_map<std::size_t, std::pair<bool, sol::state>> _activeScripts;
        std::vector<std::function<void(sol::state &)>> _setters;
    };
} // namespace GameEngine

#endif /* !SCRIPTINGSYSTEM_HPP_ */
