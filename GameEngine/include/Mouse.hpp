/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_
#include <SFML/Window/Mouse.hpp>
#include "utils/SfmlTypes.hpp"
#include "utils/Vector.hpp"

namespace GameEngine
{
    namespace Input
    {
        namespace Mouse
        {
            enum Key {
                NO_KEY,
                Left = sf::Mouse::Left,
                Right = sf::Mouse::Right,
                Middle = sf::Mouse::Middle,
            };
            static bool isKeyPressed(const Input::Mouse::Key key)
            {
                return sf::Mouse::isButtonPressed(sf::Mouse::Button(key));
            }
            static Vector2<int> getPosition(const Window &relativeTo)
            {
                sf::Vector2<int> pos = sf::Mouse::getPosition(relativeTo.getWindow());
                return Vector2<int>{pos.x, pos.y};
            }
        } // namespace Mouse
    }     // namespace Input
} // namespace GameEngine

#endif /* !MOUSE_HPP_ */
