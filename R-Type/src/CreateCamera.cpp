/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CreateCamera
*/

#include "GameManager.hpp"

void CreateCamera(GameManager &GameManager)
{
    GameEngine::Entity camera = GameManager.gameEngine.registry.spawnEntity();
    GameEngine::CameraComponent cam = {
        GameEngine::View{ GameEngine::Rect<float>(0.0f, 0.0f, 32.0f, 32.0f) }
    };

    GameManager.gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);
    auto &cameras = GameManager.gameEngine.registry.getComponent<GameEngine::CameraComponent>();
    for (size_t i = 0; i < cameras.size(); i++) {
        auto &c = cameras[i];
        if (c)
            GameManager.gameEngine.window.setView(c.value().view);
    }
}
