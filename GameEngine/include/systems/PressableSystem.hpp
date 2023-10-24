/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PressableSystem
*/

#ifndef PRESSABLESYSTEM_HPP_
#define PRESSABLESYSTEM_HPP_
#include "SparseArray.hpp"
#include "components/TransformComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/TextureComponent.hpp"
#include "Event.hpp"
#include "utils/SfmlTypes.hpp"
#include <functional>

namespace GameEngine
{
    using PressableFunction = std::function<void(SparseArray<TransformComponent> &transforms,
        SparseArray<TextureComponent> &textures, SparseArray<PressableComponent> &pressables)>;

    class PressableSystem
    {
      public:
        PressableSystem(EventManager &eventManager) : _eventManager(eventManager){};
        ~PressableSystem() = default;

        void operator()(SparseArray<TransformComponent> &transforms, SparseArray<TextureComponent> &textures,
            SparseArray<PressableComponent> &pressables);

      private:
        EventManager &_eventManager;
        bool _lastMouseState = false;
    };
} // namespace GameEngine

#endif /* !PRESSABLESYSTEM_HPP_ */
