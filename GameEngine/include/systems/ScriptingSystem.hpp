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
#include "GameEngine.hpp"
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "components/ScriptComponent.hpp"
#include "components/TransformComponent.hpp"
#include "utils/Vector.hpp"
#include "utils/Rect.hpp"

#include <iostream>

namespace GameEngine
{
    using ScriptingFunction = std::function<void(SparseArray<ScriptComponent> &)>;

    class ScriptingSystem
    {
      public:
        ScriptingSystem(GameEngine &gameEngine);
        ~ScriptingSystem() = default;

        void operator()(SparseArray<ScriptComponent> &scripts);
        void registerSetter(std::function<void(sol::state &, GameEngine &)> setter);

      private:
        void _setLua(sol::state &lua)
        {
            lua.new_usertype<Vector2<float>>("vector2f", "x", &Vector2<float>::x, "y", &Vector2<float>::y);
            lua.new_usertype<Vector2<int>>("vector2i", "x", &Vector2<int>::x, "y", &Vector2<int>::y);
            lua.new_usertype<Rect<float>>("rectf", "left", &Rect<float>::left, "top", &Rect<float>::top, "width",
                &Rect<float>::width, "height", &Rect<float>::height);
            lua.new_usertype<Rect<int>>("recti", "left", &Rect<int>::left, "top", &Rect<int>::top, "width",
                &Rect<int>::width, "height", &Rect<int>::height);
            for (auto &setter : _setters) {
                setter(lua, _gameEngine);
            };
        };

        GameEngine &_gameEngine;
        std::unordered_map<std::size_t, std::pair<bool, sol::state>> _activeScripts;
        std::vector<std::function<void(sol::state &, GameEngine &)>> _setters;
    };

    void setTransformForLua(sol::state &lua, GameEngine &engine);
    void setEntityForLua(sol::state &lua, GameEngine &engine);
} // namespace GameEngine

#endif /* !SCRIPTINGSYSTEM_HPP_ */
