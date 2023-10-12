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

        Registry registry;
        DeltaTime deltaTime;
        Window window;
        SceneManager sceneManager;

      private:
    };
} // namespace GameEngine

#endif /* !GAMEENGINE_HPP_ */
