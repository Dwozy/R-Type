/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** CameraSystem
*/

#include "systems/CameraSystem.hpp"

namespace GameEngine
{
    void CameraSystem::operator()(SparseArray<CameraComponent> &cameras, SparseArray<TransformComponent> &transforms)
    {
        for (auto &camera : cameras) {
            if (!camera || !camera->target)
                continue;
            auto &transform = transforms[camera->target.value()];
            if (!transform)
                continue;
            if (camera->follow_x)
                camera->view.setCenter({transform->position.x, camera->view.getCenter().y});
            if (camera->follow_y)
                camera->view.setCenter({camera->view.getCenter().x, transform->position.y});
        }
    }
} // namespace GameEngine