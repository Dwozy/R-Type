/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <iostream>
#include <cstdlib>
#include <functional>
#include <SFML/Graphics.hpp>
#include <utility>
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/DrawSystem.hpp"
#include "components/CameraComponent.hpp"
#include "components/FontComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/WindowComponent.hpp"
#include "utils/Vector.hpp"
#include "GameEngine.hpp"

int main(int argc, char const *argv[])
{
    GameEngine::GameEngine gameEngine(600, 600, "Demo");
    GameEngine::Entity entity = gameEngine.registry.spawnEntity();
    GameEngine::Entity camera = gameEngine.registry.spawnEntity();
    gameEngine.registry.registerComponent<GameEngine::PositionComponent>();
    gameEngine.registry.registerComponent<GameEngine::VelocityComponent>();
    gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
    gameEngine.registry.registerComponent<GameEngine::CameraComponent>();
    gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    gameEngine.registry.registerComponent<GameEngine::TextComponent>();
    GameEngine::PositionComponent pos = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::VelocityComponent vel = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::ControllableComponent con = {
        GameEngine::Input::Keyboard::Z,
        GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S,
        GameEngine::Input::Keyboard::D,
        100.0f
    };
    GameEngine::CameraComponent cam = {
        GameEngine::View{ GameEngine::Rect<float>(0.0f, 0.0f, 32.0f, 32.0f) }
    };
    gameEngine.registry.addComponent<GameEngine::PositionComponent>(entity, pos);
    gameEngine.registry.addComponent<GameEngine::VelocityComponent>(entity, vel);
    gameEngine.registry.addComponent<GameEngine::ControllableComponent>(entity, con);
    gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

    GameEngine::Texture texture;
    texture.load("../image.png", GameEngine::Rect<int>(0, 0, 32, 16));
    GameEngine::Sprite sprite;
    sprite.load(texture);
    gameEngine.registry.addComponent<GameEngine::TextureComponent>(entity, GameEngine::TextureComponent{ texture, sprite, true, 1 });

    auto &cameras = gameEngine.registry.getComponent<GameEngine::CameraComponent>();
    for (size_t i = 0; i < cameras.size(); i++) {
        auto &c = cameras[i];
        if (c)
            gameEngine.window.setView(c.value().view);
    }

    gameEngine.registry.addSystem<std::function<void(GameEngine::GameEngine &, SparseArray<GameEngine::VelocityComponent> &, SparseArray<GameEngine::ControllableComponent> &)>, GameEngine::VelocityComponent, GameEngine::ControllableComponent>(GameEngine::controlSystem, gameEngine);
    gameEngine.registry.addSystem<std::function<void(GameEngine::GameEngine &, SparseArray<GameEngine::PositionComponent> &, SparseArray<GameEngine::VelocityComponent> &, SparseArray<GameEngine::TextureComponent> &)>, GameEngine::PositionComponent, GameEngine::VelocityComponent, GameEngine::TextureComponent>(GameEngine::positionSystem, gameEngine);
    gameEngine.registry.addSystem<std::function<void(GameEngine::GameEngine &, SparseArray<GameEngine::TextComponent> &, SparseArray<GameEngine::TextureComponent> &)>, GameEngine::TextComponent, GameEngine::TextureComponent>(GameEngine::drawSystem, gameEngine);

    while (gameEngine.window.isOpen())
    {
        gameEngine.deltaTime.update();
        sf::Event event;
        while (gameEngine.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameEngine.window.close();
        }
        gameEngine.registry.runSystems();
    }
    return 0;
}
