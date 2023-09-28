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
    #include "utils/sfmlTypes.hpp"

namespace GameEngine {
    struct Font {
        std::string path;
        SFFont font;
    };
}
#endif /* !FONT_HPP_ */