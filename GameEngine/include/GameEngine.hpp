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
#include "PrefabManager.hpp"
#include "AssetManager.hpp"
#include "Event.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/AnimationSystem.hpp"
#include "components/CameraComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/FontComponent.hpp"
#include "components/MusicComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/GravityComponent.hpp"

#ifdef DEBUG
    #include "Debug.hpp"
#endif

namespace GameEngine
{
    /// @brief Game engine class, will manage all the necessary classes for the game.
    class GameEngine
    {
      public:
#ifdef DEBUG
        /// @brief Constructor for the game engine.
        /// @param maxEntities Maximum number of entities at once. Default value is 1024.
        GameEngine(std::size_t maxEntities = 1024)
            : registry(maxEntities), prefabManager(assetManager), debugMenu(eventManager, registry, deltaTime)
        {
            deltaTime.update();
        };
#else
        GameEngine(std::size_t maxEntities = 1024) : registry(maxEntities), prefabManager(assetManager)
        {
            deltaTime.update();
        };
#endif
        /// @brief Default destructor.
        ~GameEngine() = default;

        /// @brief Event manager for the game engine.
        EventManager eventManager;
        /// @brief Registry managing entities, components and systems.
        Registry registry;
        /// @brief Delta time class managing the delta time.
        DeltaTime deltaTime;
        /// @brief Window of the game.
        SceneManager sceneManager;
        AssetManager assetManager;
        PrefabManager prefabManager;
#ifdef DEBUG
        Debug::DebugMenu debugMenu;
#endif
    };
} // namespace GameEngine

#endif /* !GAMEENGINE_HPP_ */
