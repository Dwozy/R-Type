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
            Rect(T left, T top, T width, T height): left(left), top(top), width(width), height(height) {};
            ~Rect() = default;
            T left;
            T top;
            T width;
            T height;
    };
}

#endif /* !RECT_HPP_ */
