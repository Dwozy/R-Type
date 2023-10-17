/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_
#include "utils/SfmlTypes.hpp"
#include "utils/Vector.hpp"
#include <string>

namespace GameEngine
{
    struct TextComponent
    {
        std::string str;
        size_t size;
        Text text;
        bool isRendered;
        size_t renderLayer;
    };
} // namespace GameEngine

#endif /* !TEXT_HPP_ */
