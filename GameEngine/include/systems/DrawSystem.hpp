/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
#define DRAWSYSTEM_HPP_
#include "GameEngine.hpp"
#include "SFML/Graphics.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"

namespace GameEngine
{
    /// @brief Class representing the graphics rendering system
    class DrawSystem
    {
      public:
        /// @brief constructor
        /// @param window the window object of game
        DrawSystem(Window &window) : _window(window){};
        /// @brief destructor
        ~DrawSystem() = default;

        /// @brief overloaded of () operator, function that draws the textures on the window
        /// @param texts Array that contains the text components of the game
        /// @param textures Array that contains the texture components of the game
        void operator()(SparseArray<TextComponent> &texts,
                        SparseArray<TextureComponent> &textures);

      private:
        Window &_window;
    };
} // namespace GameEngine

#endif /* !DRAWSYSTEM_HPP_ */
