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
        std::string str;
        size_t size;
        Vector2<int> position;
        SFText text;
        bool isRendered;
        size_t renderLayer;
    };
}

#endif /* !TEXT_HPP_ */
