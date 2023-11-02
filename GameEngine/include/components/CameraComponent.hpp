/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CameraComponent
*/

#ifndef CAMERACOMPONENT_HPP_
#define CAMERACOMPONENT_HPP_
#include <optional>
#include "utils/SfmlTypes.hpp"
#include "Entity.hpp"

namespace GameEngine
{
    struct CameraComponent
    {
        View view;
        std::optional<size_t> target;
        bool follow_x = false;
        bool follow_y = false;
        bool isActive = true;
    };
} // namespace GameEngine

#endif /* !CAMERACOMPONENT_HPP_ */
