/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_

namespace GameEngine
{
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

        const sf::Rect<T> &getBaseRect() const { return _rect; }

      private:
        sf::Rect<T> _rect;
    };
} // namespace GameEngine

#endif /* !RECT_HPP_ */
