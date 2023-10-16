/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameLoop
*/

#include "Game.hpp"

void gameLoop(GameEngine::GameEngine &GameEngine)
{
    GameEngine::Entity ennemie = GameEngine.registry.spawnEntity();
    GameEngine::Texture texture;
    GameEngine::Sprite sprite;
    texture.load("R-Type/assets/pata_pata.gif", GameEngine::Rect<int>(0, 0 , 532, 32));
    sprite.load(texture);
    GameEngine.registry.addComponent<GameEngine::TransformComponent>(ennemie, GameEngine::TransformComponent{GameEngine::Vector2<float>(0.0f,0.0f), GameEngine::Vector2<float>(0.0f,0.0f)}),
    GameEngine.registry.addComponent<GameEngine::TextureAnimatedComponent>(ennemie, GameEngine::TextureAnimatedComponent{texture, sprite, true,
    std::vector<GameEngine::Rect<int>>{GameEngine::Rect<int>(0, 0 , 532, 32), GameEngine::Rect<int>(32, 0, 532, 32), GameEngine::Rect<int>(64, 0, 532, 32), GameEngine::Rect<int>(96, 0, 532, 32)}
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


