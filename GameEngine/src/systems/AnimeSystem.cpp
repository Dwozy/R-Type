/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimeSystem
*/

#include "systems/AnimeSystem.hpp"
#include  <iostream>
#include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    void AnimeSystem::operator()(SparseArray<TextureComponent> &texture)
    {
        float currentTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::steady_clock::now().time_since_epoch()).count();
        for (size_t i = 0; i < texture.size(); i++) {
            auto &tex = texture[i];
            if (!tex)
                return;
            if (!(tex.value().animated == true))
                return;
            if (!(currentTime - tex.value().lastUpdate > tex.value().animationSpeed))
                return;
            if (tex.value().animeid < tex.value().textureRects.size() - 1)
                tex.value().animeid += 1;
            else
                tex.value().animeid = 0;
            std::cout << tex.value().animeid << std::endl;
            std::cout << tex.value().textureRects.size() << std::endl;
            std::cout << "top " << tex.value().textureRects[tex.value().animeid].getBaseRect().top << "left " << tex.value().textureRects[tex.value().animeid].left << "width " << tex.value().textureRects[tex.value().animeid].width << "heigh " << tex.value().textureRects[tex.value().animeid].height << std::endl;
            tex.value().sprite.setTextureRect(tex.value().textureRects[tex.value().animeid]);
            tex.value().lastUpdate = currentTime;
            std::cout << "animation last udp = " << tex.value().lastUpdate << std::endl;
        }
    }
}

