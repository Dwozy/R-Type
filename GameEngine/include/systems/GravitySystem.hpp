/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GravitySystem
*/

#ifndef GRAVITYSYSTEM_HPP_
#define GRAVITYSYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "components/TransformComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/GravityComponent.hpp"

namespace GameEngine
{
    using GravityFunction = std::function<void(SparseArray<TransformComponent> &, SparseArray<GravityComponent> &)>;

    class GravitySystem {
        public:
            GravitySystem(const float &deltaTime) : _deltaTime(deltaTime){};;
            ~GravitySystem() = default;
            void operator()(SparseArray<TransformComponent> &transforms, SparseArray<GravityComponent> &gravity);
        protected:
            const float &_deltaTime;
            float _currentDeltaTime;
    };
}

#endif /* !GRAVITYSYSTEM_HPP_ */
