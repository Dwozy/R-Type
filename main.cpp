/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include "GameEngine.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "components/CameraComponent.hpp"
#include "components/FontComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/TextureComponent.hpp"
// #include "components/WindowComponent.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "utils/Vector.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <utility>

int main()
{
    // sf::RenderWindow window(sf::VideoMode(800, 600), "Demo");
    // Registry registry;
    GameEngine::GameEngine gameEngine(600, 600, "Demo");
    GameEngine::Entity entity = gameEngine.registry.spawnEntity();
    GameEngine::Entity camera = gameEngine.registry.spawnEntity();
    gameEngine.registry.registerComponent<GameEngine::PositionComponent>();
    gameEngine.registry.registerComponent<GameEngine::VelocityComponent>();
    gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
    gameEngine.registry.registerComponent<GameEngine::CameraComponent>();
    gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    gameEngine.registry.registerComponent<GameEngine::TextComponent>();
    GameEngine::PositionComponent pos = {
        GameEngine::Vector2<float>(0.0f, 0.0f)};
    GameEngine::VelocityComponent vel = {
        GameEngine::Vector2<float>(0.0f, 0.0f)};
    GameEngine::ControllableComponent con = {
        GameEngine::Input::Keyboard::Z, GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S, GameEngine::Input::Keyboard::D, 100.0f};
    GameEngine::CameraComponent cam = {
        GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 32.0f, 32.0f)}};
    gameEngine.registry.addComponent<GameEngine::PositionComponent>(entity,
                                                                    pos);
    gameEngine.registry.addComponent<GameEngine::VelocityComponent>(entity,
                                                                    vel);
    gameEngine.registry.addComponent<GameEngine::ControllableComponent>(entity,
                                                                        con);
    gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

    GameEngine::Texture texture;
    texture.load("image.png", GameEngine::Rect<int>(0, 0, 32, 16));
    GameEngine::Sprite sprite;
    sprite.load(texture);
    gameEngine.registry.addComponent<GameEngine::TextureComponent>(
        entity, GameEngine::TextureComponent{texture, sprite, true, 1});

    auto &cameras =
        gameEngine.registry.getComponent<GameEngine::CameraComponent>();
    for (size_t i = 0; i < cameras.size(); i++) {
        auto &c = cameras[i];
        if (c)
            gameEngine.window.setView(c.value().view);
    }

    GameEngine::PositionSystem positionSystem(
        gameEngine.deltaTime.getDeltaTime());
    GameEngine::ControlSystem controlSystem;
    GameEngine::DrawSystem drawSystem(gameEngine.window);

    gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::VelocityComponent> &,
                           SparseArray<GameEngine::ControllableComponent> &)>,
        GameEngine::VelocityComponent, GameEngine::ControllableComponent>(
        controlSystem);
    gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::PositionComponent> &,
                           SparseArray<GameEngine::VelocityComponent> &,
                           SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::PositionComponent, GameEngine::VelocityComponent,
        GameEngine::TextureComponent>(positionSystem);
    gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TextComponent> &,
                           SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TextComponent, GameEngine::TextureComponent>(drawSystem);

    while (gameEngine.window.isOpen()) {
        gameEngine.deltaTime.update();
        sf::Event event;
        while (gameEngine.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameEngine.window.close();
        }
        gameEngine.registry.runSystems();
    }
    return 0;
}
