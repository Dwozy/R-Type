/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include "Game.hpp"


void test(GameEngine::NoEventData event)
{
    std::cout << "Window close Event" << std::endl;
}
int main(int argc, char const *argv[])
{
    GameEngine::GameEngine gameEngine(600, 600, "Demo");
    GameEngine::Entity entity = gameEngine.registry.spawnEntity();
    GameEngine::Entity camera = gameEngine.registry.spawnEntity();
    RegisterComponent(gameEngine);
    GameEngine::PositionComponent pos = {GameEngine::Vector2<float>(0.0f, 0.0f)};
    GameEngine::VelocityComponent vel = {GameEngine::Vector2<float>(0.0f, 0.0f)};
    GameEngine::ControllableComponent con = {GameEngine::Input::Keyboard::Z, GameEngine::Input::Keyboard::Q,
    GameEngine::Input::Keyboard::S, GameEngine::Input::Keyboard::D, 100.0f};
    GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 32.0f, 32.0f)}};
    gameEngine.registry.addComponent<GameEngine::PositionComponent>(entity, pos);
    gameEngine.registry.addComponent<GameEngine::VelocityComponent>(entity, vel);
    gameEngine.registry.addComponent<GameEngine::ControllableComponent>(entity, con);
    gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

    GameEngine::Texture texture;
    texture.load("image.png", GameEngine::Rect<int>(0, 0, 32, 16));
    GameEngine::Sprite sprite;
    sprite.load(texture);
    gameEngine.registry.addComponent<GameEngine::TextureComponent>(
        entity, GameEngine::TextureComponent{texture, sprite, true, 5});

    auto &cameras = gameEngine.registry.getComponent<GameEngine::CameraComponent>();
    for (size_t i = 0; i < cameras.size(); i++) {
        auto &c = cameras[i];
        if (c)
            gameEngine.window.setView(c.value().view);
    }

    RegisterSystems(gameEngine);
    gameLoop(gameEngine);
    return 0;
}
