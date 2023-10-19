/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include <cmath>
#define VECTOR_HPP_
#include <cmath>

namespace GameEngine
{
    /// @brief a Vector2 class
    /// @tparam T the type contained in the vector
    template <typename T>
    class Vector2
    {
      public:
        /// @brief constructor
        /// @param x value of the vector
        /// @param y value of the vector
        Vector2(T x, T y) : x(x), y(y){};
        /// @brief destructor
        ~Vector2() = default;
        /// @brief calculate the length of the vector
        /// @return the length of the vector
        float length() const { return (sqrt(pow(x, 2) + pow(y, 2))); };
        /// @brief normalize the vector
        /// @return the vector normalized
        Vector2 normalize() const { return Vector2(x / length(), y / length()); };
        /// @brief calculate the dot product of the vector
        /// @param vec the vector to calculate the dot product with
        /// @return the dot product
        float dotProduct(Vector2 vec) const { return (x * vec.x + y * vec.y); };
        /// @brief overload operator == to compare two Vector2
        /// @param the vector to compare
        /// @return a boolean for the comparison
        bool operator==(const Vector2 &other) const { return (x == other.x && y == other.y); };
        /// @brief overload operator != to compare two Vector2
        /// @param the vector to compare
        /// @return a boolean for the comparison
        bool operator!=(const Vector2 &other) const { return !(*this == other); };
        /// @brief overload of the + operator
        /// @param vec the vector to add with
        /// @return the vector resulting of the addition
        Vector2 operator+(const Vector2 &vec) const { return (Vector2(x + vec.x, y + vec.y)); };
        /// @brief overload of the += operator
        /// @param vec the vector to add with
        /// @return the vector resulting of the addition
        Vector2 &operator+=(const Vector2 &vec)
        {
            x += vec.x;
            y += vec.y;
            return *this;
        };
        /// @brief overload of the - operator
        /// @param vec the vector to subtract with
        /// @return the vector resulting of the subtraction
        Vector2 operator-(const Vector2 &vec) const { return (Vector2(x + (-vec.x), y + (-vec.y))); };
        /// @brief overload of the -= operator
        /// @param vec the vector to subtract with
        /// @return result of the subtraction
        Vector2 &operator-=(const Vector2 &vec)
        {
            *this += -vec;
            return *this;
        };
        /// @brief overload of the * operator
        /// @param val the factor
        /// @return result of the multiplication
        Vector2<T> operator*(const T &val) const { return Vector2(x * val, y * val); };
        /// @brief overload of the *= operator
        /// @param val the factor
        /// @return reference to vector
        Vector2<T> &operator*=(const T &val)
        {
            x *= val;
            y *= val;
            return *this;
        };
        /// @brief overload of the / operator
        /// @param val the divisor
        /// @return result of the division
        Vector2<T> operator/(const T &val) const { return Vector2(x / val, y / val); };
        /// @brief overload of the /= operator
        /// @param val the divisor
        /// @return reference to vector
        Vector2<T> &operator/=(const T &val)
        {
            x /= val;
            y /= val;
            return *this;
        };

        T x;
        T y;
    };
} // namespace GameEngine

#endif /* !VECTOR_HPP_ */
