/*
** EPITECH PROJECT, 2023
** DamageComponent.hpp
** File description:
** DamageComponent
*/

#ifndef DAMAGECOMPONENT_HPP_
#define DAMAGECOMPONENT_HPP_

#include <cstdint>

namespace GameEngine
{
    struct DamageComponent
    {
        std::size_t damage;
        std::vector<std::size_t> listDamage;
    };
} // namespace GameEngine
#endif /* !DAMAGECOMPONENT_HPP_ */
