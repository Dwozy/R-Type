/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Nop
*/

#ifndef NOP_HPP_
    #define NOP_HPP_

namespace GameEngine
{
    struct Nop
    {
        template <typename T>
        void operator() (T const &) const noexcept { }
    };
}

#endif /* !NOP_HPP_ */
