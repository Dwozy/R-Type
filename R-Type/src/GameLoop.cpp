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
        sf::Event event;
        while (GameManager.gameEngine.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GameManager.gameEngine.window.close();
        }
        GameManager.gameEngine.registry.runSystems();
    }
}


