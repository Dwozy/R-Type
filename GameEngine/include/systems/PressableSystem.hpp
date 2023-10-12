/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PressableSystem
*/

#ifndef PRESSABLESYSTEM_HPP_
#define PRESSABLESYSTEM_HPP_
#include "SparseArray.hpp"
#include "components/PositionComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/TextureComponent.hpp"
#include "utils/SfmlTypes.hpp"
#include <functional>

namespace GameEngine
{
    using PressableFunction = std::function<void(SparseArray<PositionComponent> &positions,
        SparseArray<TextureComponent> &textures, SparseArray<PressableComponent> &pressables)>;

    class PressableSystem
    {
      public:
        PressableSystem(Window &window) : _window(window){};
        ~PressableSystem() = default;

        void operator()(SparseArray<PositionComponent> &positions, SparseArray<TextureComponent> &textures,
            SparseArray<PressableComponent> &pressables);

      private:
        Window &_window;
        bool _lastMouseState = false;
    };
} // namespace GameEngine

#endif /* !PRESSABLESYSTEM_HPP_ */
