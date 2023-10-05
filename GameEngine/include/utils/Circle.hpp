// /*
// ** EPITECH PROJECT, 2023
// ** R-Type
// ** File description:
// ** Circle
// */

// #ifndef CIRCLE_HPP_
// #define CIRCLE_HPP_
// #include "Rect.hpp"
// #include <algorithm>
// #include <cmath>

// namespace GameEngine
// {
//     class Circle
//     {
//       public:
//         Circle(const Vector2<float> &center, const float &radius)
//             : center(center), radius(radius){};
//         ~Circle() = default;

//         bool isColliding(const Vector2<float> &pos, const Rect<float> &rect,
//                          const Vector2<float> &rectPos) const
//         {
//             float posX = center.x + pos.x;
//             float posY = center.y + pos.y;
//             float rectPosX = rect.left + rectPos.x;
//             float rectPosY = rect.top + rectPos.y;
//             float x = std::clamp(rectPosX, rectPosX + rect.width, posX);
//             float y = std::clamp(rectPosY, rectPosY + rect.height, posY);
//             float dist =
//                 std::sqrtf(std::powf(x - posX, 2) + std::powf(y - posY, 2));

//             return (dist < radius);
//         };

//         /// @brief position relative
//         Vector2<float> center;
//         float radius;
//     };
// } // namespace GameEngine

// #endif /* !CIRCLE_HPP_ */
