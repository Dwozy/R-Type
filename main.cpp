/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <iostream>
#include <cstdlib>
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    // SparseArray<int> array;

    // const auto &at = array.insert_at(10, 5);
    // const auto &at = array[10];
    // std::cout << std::addressof(at) << std::endl;
    // std::cout << array.size() << std::endl;
    // for (std::size_t i = 0; i < array.size(); i++)
    // {
    //     if (array[i].has_value())
    //         std::cout << i << ". " << array[i].value() << std::endl;
    //     else
    //         std::cout << i << ". none" << std::endl;
    // }
    // std::cout << array.getIndex(at) << std::endl;



    Registry registry;
    Entity entity = registry.spawnEntity();
    registry.registerComponent<GameEngine::PositionComponent>();
    registry.registerComponent<GameEngine::VelocityComponent>();
    registry.registerComponent<GameEngine::ControllableComponent>();
    GameEngine::PositionComponent pos = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::VelocityComponent vel = { GameEngine::Vector2<float>(0.0f, 0.0f) };
    GameEngine::ControllableComponent con = {
        GameEngine::Input::Keyboard::Z,
        GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S,
        GameEngine::Input::Keyboard::D,
        0.05f
    };
    registry.addComponent<GameEngine::PositionComponent>(entity, pos);
    registry.addComponent<GameEngine::VelocityComponent>(entity, vel);
    registry.addComponent<GameEngine::ControllableComponent>(entity, con);
    // Entity entity2 = registry.spawnEntity();
    // Entity entity3 = registry.spawnEntity();
    // Entity entity4 = registry.spawnEntity();
    // Entity entity5 = registry.spawnEntity();

    // registry.killEntity(entity3);
    // entity3 = registry.spawnEntity();
    // std::cout << "ENTITY3: " << entity3 << std::endl;
    // std::cout << "ENTITY4: " << entity4 << std::endl;
    // std::cout << "ENTITY5: " << entity5 << std::endl;
    // auto &sa = registry.registerComponent<int>();
    // // sa.insert_at(entity, 5);
    // // sa.insert_at(10, 10);
    // // registry.addComponent<int>(entity, 5);
    // registry.removeComponent<int>(entity);
    // registry.registerComponent<float>().insert_at(entity2, 2);
    // auto &array = registry.getComponent<int>();
    // // array.emplace_at(1, 2, 3, 4);
    // registry.emplaceComponent<int>(entity3, entity2, entity4);
    // // registry.addComponent<int>(entity5, 10);
    // for (std::size_t i = 0; i < array.size(); i++)
    // {
    //     if (array[i].has_value())
    //         std::cout << i << ". " << array[i].value() << std::endl;
    //     else
    //         std::cout << i << ". none" << std::endl;
    // }

    sf::Texture texture;
    texture.loadFromFile("image.png", sf::IntRect(0, 0, 32, 16));
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(800, 600), "test control system");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        GameEngine::controlSystem(registry);
        GameEngine::positionSystem(registry);

        window.clear();
        auto &positions = registry.getComponent<GameEngine::PositionComponent>();
        for (size_t i = 0; i < positions.size(); i++) {
            auto &pos = positions[i];
            if (pos) {
                sprite.setPosition(sf::Vector2f(pos.value().position.x, pos.value().position.y));
                window.draw(sprite);
            }
        }
        window.display();
    }
    return 0;
}
