/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
#define DRAWSYSTEM_HPP_
#include <memory>
#include "Event.hpp"
#include "utils/SfmlTypes.hpp"
#include "SparseArray.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"

namespace GameEngine
{
    struct PollEventStruct
    {
        bool isEvent;
        SEvent event;
    };

    /// @brief Class representing the graphics rendering system
    class DrawSystem
    {
      public:
        /// @brief constructor
        /// @param width Width of the window.
        /// @param height Height of the window.
        /// @param title Title of the window.
        DrawSystem(EventManager &eventManager, int width = 1920, int height = 1080, std::string title = "default");
        /// @brief destructor
        ~DrawSystem() = default;

        /// @brief overloaded of () operator, function that draws the textures on the window
        /// @param texts Array that contains the text components of the game
        /// @param textures Array that contains the texture components of the game
        void operator()(SparseArray<TextComponent> &texts, SparseArray<TextureComponent> &textures);

      private:
        std::shared_ptr<Window> _window;
        EventManager &_eventManager;
    };
} // namespace GameEngine

#endif /* !DRAWSYSTEM_HPP_ */
