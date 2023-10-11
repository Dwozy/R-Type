/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameLoop
*/

#include "GameManager.hpp"
#include<unistd.h>
#include <iostream>
#include "Ennemies.hpp"

void test(GameManager &GameManager, GameEngine::Texture texture, GameEngine::Sprite sprite)
{
    Ennemie Patapata(GameManager.gameEngine, GameEngine::PositionComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
    GameEngine::VelocityComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
    GameEngine::TextureAnimatedComponent{texture, sprite, true, GameEngine::Rect<int>(0, 0 , 36, 36),
    GameEngine::Rect<int>(0, 0 , 36, 36), GameEngine::Rect<int>(0, 0 , 36, 36), 0.1, GameEngine::DeltaTime(), true, 2}, texture, sprite);
}

void gameLoop(GameManager &GameManager)
{
    //Ennemies ennemies(GameManager.gameEngine);

    GameEngine::Texture texture;
    GameEngine::Sprite sprite;
    texture.load("R-Type/assets/pata_pata.gif", GameEngine::Rect<int>(0, 0 , 32, 16));
    sprite.load(texture);

    test(GameManager, texture, sprite);
    // Ennemie Patapata(GameManager.gameEngine, GameEngine::PositionComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
    // GameEngine::VelocityComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
    // GameEngine::TextureAnimatedComponent{texture, sprite, true, GameEngine::Rect<int>(0, 0 , 36, 36),
    // GameEngine::Rect<int>(0, 0 , 36, 36), GameEngine::Rect<int>(0, 0 , 36, 36), 0.1, GameEngine::DeltaTime(), true, 2}, texture, sprite);

    // Ennemie enemie = create_Pata_Pata(GameManager.gameEngine);

    // ennemies.create_ennemie(0, ennemies.Pata_Pata);
    while (GameManager.gameEngine.window.isOpen())
    {
        GameManager.gameEngine.deltaTime.update();
        GameEngine::SEvent event;
        while (GameManager.gameEngine.window.pollEvent(event))
        {
            if (static_cast<size_t>(event.type) == static_cast<size_t>(GameEngine::EventT::WindowCloseEvent))
                GameManager.gameEngine.window.close();
        }
        GameManager.gameEngine.registry.runSystems();
    }
}


