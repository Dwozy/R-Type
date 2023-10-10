/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_
#include "utils/SfmlTypes.hpp"
#include "utils/Vector.hpp"
#include <string>

namespace GameEngine
{
    struct FontComponent
    {
        std::string path;
        Font font;
    };
} // namespace GameEngine
#endif /* !FONT_HPP_ */
