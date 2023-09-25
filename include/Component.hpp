/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
    #define COMPONENT_HPP_
    #include <cstdint>

namespace GameEngine
{
    /// @brief Number in uint8 which defines the ID of a component.
    using ComponentId = std::uint8_t;

    /// @brief Maximum of component that can be handle. Will mainly be used to allocate the bitset for the Signature.
    const ComponentId MAX_COMPONENT = 1;
}

#endif /* !COMPONENT_HPP_ */
