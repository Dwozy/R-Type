/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** CollisionsUtils
*/

#ifndef COLLISIONSUTILS_HPP_
#define COLLISIONSUTILS_HPP_
#include "utils/Rect.hpp"

namespace GameEngine
{
    template <typename T>
    int replaceOnTop(Vector2<T> &pos1, const Rect<T> &rect1, const Vector2<T> &pos2, const Rect<T> &rect2)
    {
        if (!rect1.isColliding(pos1, rect2, pos2))
            return -1;
        T pos1X = pos1.x + rect1.left;
        T pos1Y = pos1.y + rect1.top;
        T pos2X = pos2.x + rect2.left;
        T pos2Y = pos2.y + rect2.top;
        T x1 = std::max(pos1X, pos2X);
        T y1 = std::max(pos1Y, pos2Y);
        T x2 = std::min(pos1X + rect1.width, pos2X + rect2.width);
        T y2 = std::min(pos1Y + rect1.height, pos2Y + rect2.height);
        Vector2<T> center(pos1X + (rect1.width / 2), pos1Y + (rect1.height / 2));
        Vector2<T> rectCenter(pos2X + (rect2.width / 2), pos2Y + (rect2.height / 2));
        T diffX = center.x - rectCenter.x;
        T diffY = center.y - rectCenter.y;
        if (x2 - x1 > y2 - y1) {
            if (diffY < 0)
                pos1.y = pos2Y - rect1.height - rect1.top;
            else
                pos1.y = pos2Y + rect2.height + rect1.top;
            return 1;
        } else {
            if (diffX < 0)
                pos1.x = pos2X - rect1.width - rect1.left;
            else
                pos1.x = pos2X + rect2.width + rect1.left;
            return 0;
        }
    }
} // namespace GameEngine

#endif /* !COLLISIONSUTILS_HPP_ */
