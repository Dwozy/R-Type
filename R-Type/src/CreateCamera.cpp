/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CreateCamera
*/

#include "Game.hpp"

void CreateCamera(GameEngine::GameEngine &GameEngine)
{
    GameEngine::Entity camera = GameEngine.registry.spawnEntity();
    GameEngine::CameraComponent cam = {
        GameEngine::View{ GameEngine::Rect<float>(0.0f, 0.0f, 32.0f, 32.0f) }
    };

    GameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);
    auto &cameras = GameEngine.registry.getComponent<GameEngine::CameraComponent>();
    for (size_t i = 0; i < cameras.size(); i++) {
        auto &c = cameras[i];
        if (c)
            GameEngine.window.setView(c.value().view);
    }
}
