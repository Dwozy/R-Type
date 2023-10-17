/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ControlSystem
*/

#include "systems/ControlSystem.hpp"
#include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    void ControlSystem::operator()(
        SparseArray<TransformComponent> &transforms, SparseArray<ControllableComponent> &controllable)
    {
        for (size_t i = 0; i < controllable.size() && i < transforms.size(); i++) {
            auto &con = controllable[i];
            auto &tsf = transforms[i];
            if (con && tsf) {
                tsf.value().velocity = Vector2<float>(0.0f, 0.0f);
                tsf.value().velocity = Vector2<float>(0.0f, 0.0f);
                if (isKeyPressed(con.value().key_up))
                    tsf.value().velocity += Vector2<float>(0.0f, -1.0f);
                if (isKeyPressed(con.value().key_left))
                    tsf.value().velocity += Vector2<float>(-1.0f, 0.0f);
                if (isKeyPressed(con.value().key_down))
                    tsf.value().velocity += Vector2<float>(0.0f, 1.0f);
                if (isKeyPressed(con.value().key_right))
                    tsf.value().velocity += Vector2<float>(1.0f, 0.0f);
                if (tsf.value().velocity.x == 0.0f && tsf.value().velocity.y == 0.0f)
                    return;
                tsf.value().velocity = tsf.value().velocity.normalize();
                tsf.value().velocity.x = tsf.value().velocity.x * con.value().speed;
                tsf.value().velocity.y = tsf.value().velocity.y * con.value().speed;
            }
        }
    }
} // namespace GameEngine
