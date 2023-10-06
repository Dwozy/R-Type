/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameLoop
*/

#include "GameManager.hpp"

void gameLoop(GameManager &GameManager)
{
    while (GameManager.gameEngine.window.isOpen())
    {
        GameManager.gameEngine.deltaTime.update();
        GameEngine::SEvent eventtry;
        while (GameManager.gameEngine.window.pollEvent(eventtry))
        {
            if (static_cast<size_t>(eventtry.type) == static_cast<size_t>(GameEngine::EventT::WindowCloseEvent))
                GameManager.gameEngine.window.close();
        }
        GameManager.gameEngine.registry.runSystems();
    }
}


