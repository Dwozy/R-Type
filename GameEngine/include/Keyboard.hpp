/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_
#include <cstdint>

namespace GameEngine
{
    namespace Input
    {
        enum class InputType : uint8_t { UP = 0, RIGHT, DOWN, LEFT, SHOOT };

        struct InputInfo
        {
            std::size_t id;
            InputType idInput;
            bool state;
        };

        namespace Keyboard
        {

            enum Key {
                NO_KEY,
                A,
                B,
                C,
                D,
                E,
                F,
                G,
                H,
                I,
                J,
                K,
                L,
                M,
                N,
                O,
                P,
                Q,
                R,
                S,
                T,
                U,
                V,
                W,
                X,
                Y,
                Z,
                Num0,
                Num1,
                Num2,
                Num3,
                Num4,
                Num5,
                Num6,
                Num7,
                Num8,
                Num9,
                Escape,
                LControl,
                LShift,
                LAlt,
                LSystem,
                RControl,
                RShift,
                RAlt,
                RSystem,
                Menu,
                LBracket,
                RBracket,
                Semicolon,
                Comma,
                Period,
                Quote,
                Slash,
                Backslash,
                Tilde,
                Equal,
                Dash,
                Space,
                Enter,
                Backspace,
                Tab,
                Add,
                Subtract,
                Multiply,
                Divide,
                Left,
                Right,
                Up,
                Down,
                Numpad0,
                Numpad1,
                Numpad2,
                Numpad3,
                Numpad4,
                Numpad5,
                Numpad6,
                Numpad7,
                Numpad8,
                Numpad9,
                F1,
                F2,
                F3,
                F4,
                F5,
                F6,
                F7,
                F8,
                F9,
                F10,
                F11,
                F12,
                F13,
                F14,
                F15,
                Pause
            };

        } // namespace Keyboard
    }     // namespace Input
} // namespace GameEngine

#endif /* !INPUT_HPP_ */
