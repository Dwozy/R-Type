/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GravitySystem
*/

#include "systems/GravitySystem.hpp"

namespace GameEngine
{
    void GravitySystem::operator()(SparseArray<TransformComponent> &transforms, SparseArray<TextureComponent> &textures, SparseArray<GravityComponent> &gravity)
    {
        _currentDeltaTime += _deltaTime;
        for (size_t i = 0; i < gravity.size(); ++i)
        {
            auto &tsf = transforms[i];
            auto &tex = textures[i];
            auto &grav = gravity[i];
            if (!(_currentDeltaTime >= 0.001))
                return;
            _currentDeltaTime = 0;
            if (tsf && grav) {
                std::cout << " x = " << tsf->position.x << " y = " << tsf->position.y << std::endl;
                tsf->velocity += grav->gravityForce;
            }
            if (tsf && tex)
                tex.value().sprite.setPosition(tsf.value().position);
        }
    }
}
