/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CameraSystem
*/

#ifndef CAMERASYSTEM_HPP_
#define CAMERASYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "components/CameraComponent.hpp"
#include "components/TransformComponent.hpp"

namespace GameEngine
{
    class CameraSystem
    {
      public:
        CameraSystem() = default;
        ~CameraSystem() = default;

        void operator()(SparseArray<CameraComponent> &cameras, SparseArray<TransformComponent> &transforms);
    };
} // namespace GameEngine

#endif /* !CAMERASYSTEM_HPP_ */
