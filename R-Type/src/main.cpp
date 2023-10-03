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
#include "components/CameraComponent.hpp"
#include "utils/Vector.hpp"
#include "GameEngine.hpp"
#include "GameManager.hpp"

int main(int argc, char const *argv[])
{
    GameManager GameManager(600, 600, "demo");
    RegisterComponent(GameManager);
    Player player(GameManager, { GameEngine::Vector2<float>(0.0f, 0.0f) }, { GameEngine::Vector2<float>(0.0f, 0.0f) }, {
        GameEngine::Input::Keyboard::Z,
        GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S,
        GameEngine::Input::Keyboard::D,
        100.0f
    });
    CreateCamera(GameManager);
    RegisterSystems(GameManager);
    gameLoop(GameManager);
    return 0;
}
