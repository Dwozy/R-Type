/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DeltaTime
*/

#include "utils/DeltaTime.hpp"

GameEngine::DeltaTime::DeltaTime()
{
    _lastTime = std::chrono::steady_clock::now();
    float _deltaTime = 0;
}

void GameEngine::DeltaTime::update()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<float> dTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTime);

    _deltaTime = dTime.count();
    _lastTime = now;
}

const float &GameEngine::DeltaTime::getDeltaTime() const { return _deltaTime; }
