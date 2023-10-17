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
#include "components/RectCollider.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/ViewComponent.hpp"
#include "components/WindowComponent.hpp"

namespace GameEngine
{
    class GameEngine
    {
      public:
        GameEngine(
            int width = 1920, int height = 1080, std::string windowName = "default", std::size_t maxEntities = 512)
            : window(width, height, windowName), registry(maxEntities)
        {
            deltaTime.update();
        };
        ~GameEngine() = default;

        EventMananger eventManager;
        Window window;
        Registry registry;
        DeltaTime deltaTime;
        SceneManager sceneManager;

      private:
    };
} // namespace GameEngine

#endif /* !GAMEENGINE_HPP_ */
