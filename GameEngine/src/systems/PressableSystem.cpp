/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PressableSystem
*/

#include "systems/PressableSystem.hpp"
#include "Mouse.hpp"
#include <iostream>

namespace GameEngine
{
    void PressableSystem::operator()(SparseArray<TransformComponent> &transforms,
        SparseArray<TextureComponent> &textures, SparseArray<PressableComponent> &pressables)
    {
        Vector2<float> coord = _window.mapPixelToCoords(Input::Mouse::getPosition(_window));
        Vector2<int> mousePos(coord.x, coord.y);
        bool mousePressed = Input::Mouse::isKeyPressed(Input::Mouse::Left);

        for (std::size_t i = 0; i < transforms.size(); i++) {
            auto &tsf = transforms[i];
            auto &tex = textures[i];
            auto &pre = pressables[i];

            if (!tsf || !tex || !pre)
                continue;
            Vector2<int> intPos(tsf.value().position.x, tsf.value().position.y);
            if (pre.value().hitbox.isColliding(intPos, Recti(0, 0, 1, 1), mousePos)) {
                if (!mousePressed && pre.value().state == pressedState) {
                    tex.value().sprite.setRect(pre.value().textureHovered);
                    pre.value().state = hoveredState;
                    return pre.value().action();
                }
                if (!mousePressed && pre.value().state != hoveredState) {
                    tex.value().sprite.setRect(pre.value().textureHovered);
                    pre.value().state = hoveredState;
                    continue;
                }
                if (mousePressed && pre.value().state != pressedState) {
                    tex.value().sprite.setRect(pre.value().texturePressed);
                    pre.value().state = pressedState;
                    continue;
                }
            } else if (pre.value().state != defaultState) {
                tex.value().sprite.setRect(pre.value().textureDefault);
                pre.value().state = defaultState;
            }
        }
        _lastMouseState = mousePressed;
    }
} // namespace GameEngine
