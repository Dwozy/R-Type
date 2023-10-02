/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_
    #include "utils/Vector.hpp"
    #include "utils/sfmlTypes.hpp"

namespace GameEngine {
    struct Window {
        Vector2<int> size;
        SFWindow window;
    };
}


#endif /* !WINDOW_HPP_ */
