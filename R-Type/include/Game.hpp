/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Game
*/

#ifndef GAMEMANAGER_HPP_
    #define GAMEMANAGER_HPP_
    #include <cstddef>
    #include <iostream>
    #include <cstdlib>
    #include <functional>
    #include <utility>
    #include "SparseArray.hpp"
    #include "Registry.hpp"
    #include "components/CameraComponent.hpp"
    #include "utils/Vector.hpp"
    #include "GameEngine.hpp"
    #include "Event.hpp"

void CreateCamera(GameEngine::GameEngine &GameEngine);
void CreatePlayer(GameEngine::GameEngine &GameEngine);
void RegisterComponent(GameEngine::GameEngine &GameEngine);
void RegisterSystems(GameEngine::GameEngine &GameEngine);
void gameLoop(GameEngine::GameEngine &GameEngine);

#endif /* !GAMEMANAGER_HPP_ */
