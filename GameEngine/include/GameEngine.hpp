/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
    #define GAMEENGINE_HPP_
    #include "Registry.hpp"
    #include "utils/SfmlTypes.hpp"
    #include "utils/DeltaTime.hpp"

namespace GameEngine
{
    class GameEngine
    {
        public:
            GameEngine(int width = 1920, int height = 1080, std::string windowName = "default"): window(width, height, windowName)
            {
                deltaTime.update();
            };
            ~GameEngine() = default;

            Registry registry;
            DeltaTime deltaTime;
            Window window;
        private:
    };
}

#endif /* !GAMEENGINE_HPP_ */
