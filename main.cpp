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
#include "components/CameraComponent.hpp"
#include "Components/FontComponent.hpp"
#include "Components/TextureComponent.hpp"
#include "Components/TextComponent.hpp"
#include "Components/WindowComponent.hpp"
#include "utils/Vector.hpp"
#include "Systems.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Demo");
    Registry registry;
    Entity entity = registry.spawnEntity();
    Entity camera = registry.spawnEntity();
    registry.registerComponent<GameEngine::PositionComponent>();
    registry.registerComponent<GameEngine::VelocityComponent>();
    registry.registerComponent<GameEngine::ControllableComponent>();
    registry.registerComponent<GameEngine::CameraComponent>();
    registry.registerComponent<GameEngine::TextureComponent>();
    registry.registerComponent<GameEngine::Text>();
    GameEngine::PositionComponent pos = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::VelocityComponent vel = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::ControllableComponent con = {
        GameEngine::Input::Keyboard::Z,
        GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S,
        GameEngine::Input::Keyboard::D,
        0.05f
    };
    GameEngine::CameraComponent cam = {
        GameEngine::View{ GameEngine::Rect<float>(0.0f, 0.0f, 32.0f, 32.0f) }
    };
    registry.addComponent<GameEngine::PositionComponent>(entity, pos);
    registry.addComponent<GameEngine::VelocityComponent>(entity, vel);
    registry.addComponent<GameEngine::ControllableComponent>(entity, con);
    registry.addComponent<GameEngine::CameraComponent>(camera, cam);

    GameEngine::SFTexture texture;
    texture.load("image.png", GameEngine::Rect<int>(0, 0, 32, 16));
    GameEngine::SFSprite sprite;
    sprite.load(texture);
    registry.addComponent<GameEngine::TextureComponent>(entity, GameEngine::TextureComponent{ texture, sprite, true, 1 });

    auto &cameras = registry.getComponent<GameEngine::CameraComponent>();
    for (size_t i = 0; i < cameras.size(); i++) {
        auto &c = cameras[i];
        if (c)
            window.setView(c.value().view.getBaseView());
    }

    registry.addSystem<std::function<void(Registry &, SparseArray<GameEngine::VelocityComponent> &, SparseArray<GameEngine::ControllableComponent> &)>, GameEngine::VelocityComponent, GameEngine::ControllableComponent>(GameEngine::controlSystem);
    registry.addSystem<std::function<void(Registry &, SparseArray<GameEngine::PositionComponent> &, SparseArray<GameEngine::VelocityComponent> &, SparseArray<GameEngine::TextureComponent> &)>, GameEngine::PositionComponent, GameEngine::VelocityComponent, GameEngine::TextureComponent>(GameEngine::positionSystem);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        registry.runSystems();
        GameEngine::SystemDraw(registry, window);
    }
    return 0;
}
