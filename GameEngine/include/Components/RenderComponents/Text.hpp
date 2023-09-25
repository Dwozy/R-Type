/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_
    #include <string>
    #include "utils/Vector.hpp"
    #include "utils/sfmlTypes.hpp"

namespace GameEngine
{
    struct Text
    {
        std::string tt;
        Vector2<int> position;
        Font font;
    };
}

#endif /* !TEXT_HPP_ */
