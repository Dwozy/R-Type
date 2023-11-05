/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** ScriptingSystem
*/

#include "systems/ScriptingSystem.hpp"
#include "components/TransformComponent.hpp"

#include <iostream>

namespace GameEngine
{
    ScriptingSystem::ScriptingSystem(Registry &registry) : _registry(registry) {}

    void ScriptingSystem::operator()(SparseArray<ScriptComponent> &scripts)
    {
        for (std::size_t i = 0; i < scripts.size(); i++) {
            auto &script = scripts[i];

            if (!script)
                continue;
            if (_activeScripts.find(i) == _activeScripts.end()) {
                sol::state lua;
                lua.open_libraries(sol::lib::base);
                _setLua(lua);
                lua.script_file(script->name);
                sol::function start = lua["Start"];
                if (start.valid())
                    start();
                _activeScripts.insert({i, std::make_pair(true, std::move(lua))});
                // lua["GameEngine::TransformComponent"]["position"] = &GameEngine::TransformComponent::position;
            } else {
                sol::function update = _activeScripts[i].second["Update"];
                if (update.valid())
                    update();
                _activeScripts[i].first = true;
            }
        }
        for (auto i = _activeScripts.begin(); i != _activeScripts.end(); i++) {
            if (!i->second.first) {
                _activeScripts.erase(i);
                continue;
            }
            i->second.first = false;
        }
    }
} // namespace GameEngine
