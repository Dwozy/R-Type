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
        GameEngine::Event eventtry;
        sf::Event event;
        while (GameManager.gameEngine.window.pollEvent(eventtry))
        {
            if (eventtry.type == GameEngine::Event::EvenType::WindowCloseEvent)
                GameManager.gameEngine.window.close();
        }
        GameManager.gameEngine.registry.runSystems();
    }
}


