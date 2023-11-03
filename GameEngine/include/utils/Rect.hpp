/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_
#include "RenderInterfaces.hpp"
#include "utils/Vector.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace GameEngine
{
    // class Circle;

    /// @brief class representing a rect
    /// @tparam T the type contained in the rect
    template <typename T>
    class Rect : public IRect<T, sf::Rect>
    {
      public:
        /// @brief constructor
        Rect() = default;
        /// @brief constructor
        /// @param l left coordinate
        /// @param t top coordinate
        /// @param w the width of the rect
        /// @param h the height of the rect
        Rect(T l, T t, T w, T h) : left(l), top(t), width(w), height(h){};
        /// @brief destructor
        ~Rect() = default;
        T left;
        T top;
        T width;
        T height;

        /// @brief get the rect stored in the class
        /// @return rect of type T
        const sf::Rect<T> getBaseRect() const override { return sf::Rect<T>(left, top, width, height); };

        /// @brief check the collision between two objects
        /// @param pos
        /// @param rect
        /// @param rectPos position of rect
        /// @return boolean that indicates if a collision is made
        bool isColliding(const Vector2<T> &pos, const Rect<T> &rect, const Vector2<T> &rectPos) const
        {
            T posX = pos.x + left;
            T posY = pos.y + top;
            T rectPosX = rectPos.x + rect.left;
            T rectPosY = rectPos.y + rect.top;

            return (posX < rectPosX + rect.width && posX + width > rectPosX && posY < rectPosY + rect.height &&
                    posY + height > rectPosY);
        };

        /// @brief
        /// @param pos
        /// @param rect
        /// @param rectPos
        void handleCollisionFromRect(Vector2<T> &pos, const Rect<T> &rect, const Vector2<T> &rectPos)
        {
            if (!isColliding(pos, rect, rectPos))
                return;
            Vector2<T> center(pos.x + (width / 2), pos.y + (height / 2));
            Vector2<T> rectCenter(rectPos.x + (rect.width / 2), rectPos.y + (rect.height / 2));
            T diffX = center.x - rectCenter.x;
            T diffY = center.y - rectCenter.y;
            if (std::abs(diffX / width) < std::abs(diffY / height)) {
                if (diffX < 0)
                    pos.x = rectPos.x - width;
                else
                    pos.x = rectPos.x + rect.width;
            } else {
                if (diffY < 0)
                    pos.y = rectPos.y - height;
                else
                    pos.y = rectPos.y + rect.height;
            }
        }
    };

    using Rectf = Rect<float>;
    using Recti = Rect<int>;

} // namespace GameEngine

#endif /* !RECT_HPP_ */
