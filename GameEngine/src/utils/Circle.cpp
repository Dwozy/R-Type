// /*
// ** EPITECH PROJECT, 2023
// ** R-Type
// ** File description:
// ** Circle
// */

// #include "utils/Circle.hpp"

// bool GameEngine::Circle::isColliding(const Vector2<float> &pos,
//                                      const Rect<float> &rect,
//                                      const Vector2<float> &rectPos) const
// {
//     float posX = center.x + pos.x;
//     float posY = center.y + pos.y;
//     float rectPosX = rect.left + rectPos.x;
//     float rectPosY = rect.top + rectPos.y;
//     float x = std::clamp(rectPosX, rectPosX + rect.width, posX);
//     float y = std::clamp(rectPosY, rectPosY + rect.height, posY);
//     float dist = std::sqrt(std::pow(x - posX, 2) + std::pow(y - posY, 2));

//     return (dist < radius);
// }

// bool GameEngine::Circle::isColliding(const Vector2<float> &pos,
//                                      const Circle &circle,
//                                      const Vector2<float> &circlePos) const
// {
//     float distX = (center.x + pos.x) - (circle.center.x + circlePos.x);
//     float distY = (center.y + pos.y) - (circle.center.y + circlePos.y);
//     float dist = std::sqrt( std::pow(distX, 2) + std::pow(distY, 2));

//     return (dist <= (radius + circle.radius));
// }
