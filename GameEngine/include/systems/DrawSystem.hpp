/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DrawSystem
*/

#ifndef DRAWSYSTEM_HPP_
    #define DRAWSYSTEM_HPP_
    #include "SFML/Graphics.hpp"
    #include "GameEngine.hpp"
    #include "components/TextureComponent.hpp"
    #include "components/TextComponent.hpp"

namespace GameEngine
{
    void drawSystem(GameEngine &gameEngine, SparseArray<TextComponent> &texts, SparseArray<TextureComponent> &textures);
}

#endif /* !DRAWSYSTEM_HPP_ */
