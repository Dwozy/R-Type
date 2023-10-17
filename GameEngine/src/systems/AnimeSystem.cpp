/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimeSystem
*/

#include "systems/AnimeSystem.hpp"
#include <iostream>
#include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    void AnimeSystem::operator()(SparseArray<TextureComponent> &texture)
    {
        _currentDeltaTime += _deltaTime;
        for (size_t i = 0; i < texture.size(); i++) {
            auto &tex = texture[i];
            if (!tex)
                return;
            if (!(tex.value().animated == true))
                return;
            if (!(_currentDeltaTime >= tex.value().animationSpeed))
                return;
            _currentDeltaTime = 0;
            if (tex.value().animeid < tex.value().textureRects.size() - 1)
                tex.value().animeid += 1;
            else
                tex.value().animeid = 0;
            tex.value().sprite.setTextureRect(tex.value().textureRects[tex.value().animeid]);
        }
    }
} // namespace GameEngine
