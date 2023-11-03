/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#include "systems/AnimationSystem.hpp"
#include <iostream>
#include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    void AnimationSystem::operator()(SparseArray<TextureComponent> &textures)
    {
        for (size_t i = 0; i < textures.size(); i++) {
            auto &tex = textures[i];
            if (!tex)
                continue;
            if (!tex.value().animated)
                continue;
            tex.value().lastUpdate += _deltaTime;
            if (tex.value().lastUpdate < tex.value().animationSpeed)
                continue;
            if (tex.value().animeid < tex.value().textureRects.size() - 1)
                tex.value().animeid += 1;
            else
                tex.value().animeid = 0;
            tex.value().sprite.setTextureRect(tex.value().textureRects[tex.value().animeid]);
            tex.value().lastUpdate = 0;
        }
        // _currentDeltaTime = 0;
    }
} // namespace GameEngine
