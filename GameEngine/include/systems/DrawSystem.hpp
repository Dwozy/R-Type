/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
#define DRAWSYSTEM_HPP_
#include "GameEngine.hpp"
#include "components/TextComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextureAnimatedComponent.hpp"
#include <SFML/Graphics.hpp>

namespace GameEngine
{
    class DrawSystem
    {
      public:
        DrawSystem(Window &window) : _window(window){};
        ~DrawSystem() = default;

        void operator()(SparseArray<TextComponent> &texts,
                        SparseArray<TextureComponent> &textures,
                        SparseArray<TextureAnimatedComponent> &texturesA);

      private:
        Window &_window;
    };
} // namespace GameEngine

#endif /* !DRAWSYSTEM_HPP_ */
