/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameLoop
*/

#include "Game.hpp"

// void test(GameEngine::GameEngine &GameEngine)
// {
//     GameEngine::Texture texture;
//     GameEngine::Sprite sprite;
//     texture.load("R-Type/assets/pata_pata.gif", GameEngine::Rect<int>(0, 0 , 32, 16));
//     sprite.load(texture);
//     Ennemie Patapata(gameEngine, GameEngine::PositionComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
//     GameEngine::VelocityComponent{GameEngine::Vector2<float>(0.0f, 0.0f)},
//     GameEngine::TextureAnimatedComponent{texture, sprite, true, GameEngine::Rect<int>(0, 0 , 36, 36),
//     GameEngine::Rect<int>(0, 0 , 36, 36), GameEngine::Rect<int>(0, 0 , 36, 36), 0.1, GameEngine::DeltaTime(), true, 2}, texture, sprite);
// }

void gameLoop(GameEngine::GameEngine &GameEngine)
{
    GameEngine::Entity ennemie = GameEngine.registry.spawnEntity();
    GameEngine::Texture texture;
    GameEngine::Sprite sprite;
    texture.load("R-Type/assets/pata_pata.gif", GameEngine::Rect<int>(0, 0 , 32, 32));
    sprite.load(texture);
    GameEngine.registry.addComponent<GameEngine::PositionComponent>(ennemie, GameEngine::PositionComponent{GameEngine::Vector2<float>(0.0f, 0.0f)});
    GameEngine.registry.addComponent<GameEngine::VelocityComponent>(ennemie, GameEngine::VelocityComponent{GameEngine::Vector2<float>(0.0f, 0.0f)});
    GameEngine.registry.addComponent<GameEngine::TextureAnimatedComponent>(ennemie, GameEngine::TextureAnimatedComponent{texture, sprite, true,
    std::vector<GameEngine::Rect<int>>{GameEngine::Rect<int>(0, 0 , 32, 32), GameEngine::Rect<int>(32, 0, 32, 32), GameEngine::Rect<int>(64, 0, 32, 32), GameEngine::Rect<int>(96, 0, 32, 32)}
    , 5, true, 0, 0, 5});
    while (GameEngine.window.isOpen())
    {
        GameEngine.deltaTime.update();
        GameEngine::SEvent event;
        while (GameEngine.window.pollEvent(event))
        {
            if (static_cast<size_t>(event.type) == static_cast<size_t>(GameEngine::EventT::WindowCloseEvent))
                GameEngine.window.close();
        }
        GameEngine.registry.runSystems();
    }
}


