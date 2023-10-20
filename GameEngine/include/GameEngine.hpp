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
#include "utils/PrefabManager.hpp"
#include "Event.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/AnimeSystem.hpp"
#include "components/CameraComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/FontComponent.hpp"
#include "components/MusicComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/TransformComponent.hpp"

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

        /// @brief Event manager for the game engine.
        EventMananger eventManager;
        /// @brief Registry managing entities, components and systems.
        Registry registry;
        /// @brief Delta time class managing the delta time.
        DeltaTime deltaTime;
        /// @brief Window of the game.
        Window window;
        /// @brief Scene manager, use it to register scene, loading and unloading them.
        SceneManager sceneManager;
        PrefabManager prefabManager;
    };
} // namespace GameEngine

#endif /* !GAMEENGINE_HPP_ */
