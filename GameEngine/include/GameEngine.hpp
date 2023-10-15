/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "utils/DeltaTime.hpp"
#include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    /// @brief Game engine class, will manage all the necessary classes for the game.
    class GameEngine
    {
      public:
        /// @brief Constructor for the game engine.
        /// @param width Width of the window. Default value is 1920.
        /// @param height Height of the window. Default value is 1080.
        /// @param windowName Name of the window. Default value is default.
        /// @param maxEntities Maximum number of entities at once. Default value is 512.
        GameEngine(
            int width = 1920, int height = 1080, std::string windowName = "default", std::size_t maxEntities = 512)
            : window(width, height, windowName), registry(maxEntities)
        {
            deltaTime.update();
        };
        /// @brief Default destructor.
        ~GameEngine() = default;

        /// @brief Registry managing entities, components and systems.
        Registry registry;
        /// @brief Delta time class managing the delta time.
        DeltaTime deltaTime;
        /// @brief Window of the game.
        Window window;
        /// @brief Scene manager, use it to register scene, loading and unloading them.
        SceneManager sceneManager;
    };
} // namespace GameEngine

#endif /* !GAMEENGINE_HPP_ */
