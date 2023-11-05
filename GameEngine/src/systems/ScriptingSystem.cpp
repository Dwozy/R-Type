/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** ScriptingSystem
*/

#include <iostream>
#include "systems/ScriptingSystem.hpp"
#include "components/TransformComponent.hpp"
#include "Error.hpp"

namespace GameEngine
{
    ScriptingSystem::ScriptingSystem(GameEngine &gameEngine) : _gameEngine(gameEngine) {}

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
                std::cout << "Entity ID " << i << std::endl;
                if (start.valid())
                    start(i);
                _activeScripts.insert({i, std::make_pair(true, std::move(lua))});
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

    void ScriptingSystem::registerSetter(std::function<void(sol::state &, GameEngine &)> setter)
    {
        _setters.push_back(setter);
    }

    void setTransformForLua(sol::state &lua, GameEngine &engine)
    {
        lua.new_usertype<TransformComponent>(
            "transform", "position", &TransformComponent::position, "velocity", &TransformComponent::velocity);
        lua.set_function("get_position", [&engine](std::size_t idx) {
            auto &tsfs = engine.registry.getComponent<TransformComponent>();
            std::optional<std::shared_ptr<Vector2<float>>> pos;
            if (tsfs[idx].has_value()) {
                std::shared_ptr<Vector2<float>> ptr(&tsfs[idx].value().position, [](void *) {});
                pos = ptr;
            }
            return pos;
        });
        lua.set_function("get_velocity", [&engine](std::size_t idx) {
            auto &tsfs = engine.registry.getComponent<TransformComponent>();
            std::optional<std::shared_ptr<Vector2<float>>> pos;
            if (tsfs[idx].has_value()) {
                std::shared_ptr<Vector2<float>> ptr(&tsfs[idx].value().velocity, [](void *) {});
                pos = ptr;
            }
            return pos;
        });
    }

    void setEntityForLua(sol::state &lua, GameEngine &engine)
    {
        lua.set_function("spawn_entity", [&engine]() {
            std::size_t entity = engine.registry.spawnEntity();
            return entity;
        });
        lua.set_function("kill_entity", [&engine](std::size_t entity) {
            try {
                Entity kill = engine.registry.getEntityById(entity);
                engine.registry.killEntity(kill);
            } catch (Error::InvalidEntityIdError()) {
                std::cout << "Invalid entity" << std::endl;
            };
        });
    }
} // namespace GameEngine
