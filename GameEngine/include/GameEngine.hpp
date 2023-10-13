/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_
#include "Registry.hpp"
#include "utils/DeltaTime.hpp"
#include "utils/SfmlTypes.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/AnimeSystem.hpp"
#include "components/CameraComponent.hpp"
#include "components/FontComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/TextureAnimatedComponent.hpp"

namespace GameEngine
{
    class GameEngine
    {
      public:
        GameEngine(int width = 1920, int height = 1080,
                   std::string windowName = "default")
            : window(width, height, windowName)
        {
            deltaTime.update();
        };
        ~GameEngine() = default;

        Registry registry;
        DeltaTime deltaTime;
        Window window;

      private:
    };
} // namespace GameEngine

#endif /* !GAMEENGINE_HPP_ */
