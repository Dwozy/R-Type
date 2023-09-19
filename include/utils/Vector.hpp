/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
    #define VECTOR_HPP_
    #include <cmath>

class Vector2
{
    public:
        Vector2(float x, float y): x(x), y(y) {};
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
        float x;
        float y;
};

class Vector2Int
{
    public:
        Vector2Int(int x, int y): x(x), y(y) {};
        ~Vector2Int() = default;
        float length()
        {
            return (sqrt(pow(x, 2)+ pow(y, 2)));
        }
        Vector2 normalize() {
            return Vector2(x / length(), y / length());
        }
        float dotProduct(Vector2 vec)
        {
            return (x * vec.x + y * vec.y);
        }
        int x;
        int y;
};

#endif /* !VECTOR_HPP_ */
