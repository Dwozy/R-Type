/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ControlSystem
*/

#include "systems/ControlSystem.hpp"

namespace GameEngine
{
    void controlSystem(GameEngine &gameEngine,
                       SparseArray<VelocityComponent> &velocities,
                       SparseArray<ControllableComponent> &controllable)
    {
        for (size_t i = 0; i < controllable.size() && i < velocities.size();
             i++) {
            auto &con = controllable[i];
            auto &vel = velocities[i];
            if (con && vel) {
                vel.value().velocity = Vector2<float>(0.0f, 0.0f);
                if (Input::Keyboard::isKeyPressed(con.value().key_up))
                    vel.value().velocity += Vector2<float>(0.0f, -1.0f);
                if (Input::Keyboard::isKeyPressed(con.value().key_left))
                    vel.value().velocity += Vector2<float>(-1.0f, 0.0f);
                if (Input::Keyboard::isKeyPressed(con.value().key_down))
                    vel.value().velocity += Vector2<float>(0.0f, 1.0f);
                if (Input::Keyboard::isKeyPressed(con.value().key_right))
                    vel.value().velocity += Vector2<float>(1.0f, 0.0f);
                if (vel.value().velocity.x == 0.0f &&
                    vel.value().velocity.y == 0.0f)
                    return;
                vel.value().velocity = vel.value().velocity.normalize();
                vel.value().velocity.x =
                    vel.value().velocity.x * con.value().speed;
                vel.value().velocity.y =
                    vel.value().velocity.y * con.value().speed;
            }
        }
    }
} // namespace GameEngine
