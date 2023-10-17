/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Font
*/

#ifndef FONT_HPP_
#define FONT_HPP_
#include <string>
#include "utils/Vector.hpp"
#include "utils/RenderInterfaces.hpp"

namespace GameEngine
{
    struct FontComponent
    {
        std::string path;
        Font font;
    };
} // namespace GameEngine
#endif /* !FONT_HPP_ */
