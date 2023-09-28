/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
    #define VECTOR_HPP_
    #include <cmath>

namespace GameEngine
{
    template <typename T>
    class Vector2
    {
        public:
            Vector2(T x, T y): x(x), y(y) {};
            ~Vector2() = default;
            float length()
            {
                return (sqrt(pow(x, 2)+ pow(y, 2)));
            }
            Vector2 normalize()
            {
                return Vector2(x / length(), y / length());
            }
            float dotProduct(Vector2 vec)
            {
                return (x * vec.x + y * vec.y);
            }
            Vector2 operator+(const Vector2 &vec) {
                return (Vector2(x + vec.x, y + vec.y));
            }
            Vector2 operator+=(const Vector2 &vec) {
                return (Vector2(x += vec.x, y += vec.y));
            }
            Vector2 operator-(const Vector2 &vec) {
                return (Vector2(x + (-vec.x), y + (-vec.y)));
            }
            Vector2 operator-=(const Vector2 &vec) {
                return (Vector2(x -= vec.x, y -= vec.y));
            }
            T operator*(const Vector2 &vec) {
                return (y * vec.y + x * vec.x);
            }
            T x;
            T y;
    };
}

#endif /* !VECTOR_HPP_ */
