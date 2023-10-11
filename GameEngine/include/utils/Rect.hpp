/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_
#include "utils/Vector.hpp"
#include <algorithm>
#include <cmath>

namespace GameEngine
{
    class Circle;

    template <typename T>
    class Rect
    {
      public:
        Rect(T left, T top, T width, T height) { _rect = sf::Rect{left, top, width, height}; };
        ~Rect() = default;
        T &left = _rect.left;
        T &top = _rect.top;
        T &width = _rect.width;
        T &height = _rect.height;

        const sf::Rect<T> &getBaseRect() const { return _rect; };

        // bool isColliding(const Vector2<T> &pos, const Rect<T> &rect,
        //                  const Vector2<T> &rectPos) const
        // {
        //     T posX = pos.x + left;
        //     T posY = pos.y + top;
        //     T rectPosX = rectPos.x + rect.left;
        //     T rectPosY = rectPos.y + rect.top;

        //     return (posX < rectPosX + rect.width && posX + width > rectPosX &&
        //             posY < rectPosY + rect.height && posY + height > rectPosY);
        // };
        // bool isColliding(const Vector2<T> &pos, const Circle &circle,
        //                  const Vector2<T> &circlePos) const
        // {
        //     float posX = left + pos.x;
        //     float posY = top + pos.y;
        //     float circlePosX = circle.center.x + circlePos.x;
        //     float circlePosY = circle.center.y + circlePos.y;
        //     float x = std::clamp(posX, posX + width, circlePosX);
        //     float y = std::clamp(posY, posY + height, circlePosY);
        //     float dist =
        //         std::sqrtf(std::powf(x - posX, 2) + std::powf(y - posY, 2));

        //     return (dist < radius);
        // };

      private:
        sf::Rect<T> _rect;
    };
} // namespace GameEngine

#endif /* !RECT_HPP_ */
