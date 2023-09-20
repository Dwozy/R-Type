/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
    #define VECTOR_HPP_

namespace
{
    class Vector2Int
    {
        public:
            Vector2Int(int x, int y): x(x), y(y) {};
            ~Vector2Int() = default;

            int x;
            int y;
    };

    class Vector2
    {
        public:
            Vector2(float x, float y): x(x), y(y) {};
            ~Vector2() = default;

            float x;
            float y;
    };
}

#endif /* !VECTOR_HPP_ */
