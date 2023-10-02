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
    struct WindowComponent {
        Vector2<int> size;
        Window window;
    };
}


#endif /* !WINDOW_HPP_ */
