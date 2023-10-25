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
        /// @param maxEntities Maximum number of entities at once. Default value is 512.
        GameEngine(std::size_t maxEntities = 512) : registry(maxEntities), prefabManager(assetManager)
        {
            deltaTime.update();
            assetManager.loadTexture("R-Type/assets/image.png", {0, 0, 32, 16});
        };
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
    };
} // namespace GameEngine

#endif /* !GAMEENGINE_HPP_ */
