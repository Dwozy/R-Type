/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <cstdlib>

namespace GameEngine
{
    class Registry;

    /// @brief Entity class for the game engine.
    class Entity
    {
      public:
        friend class Registry;
        /// @brief Default destructor.
        ~Entity() = default;

        /// @brief Overload to be able to use the entity as a size_t.
        operator std::size_t() const { return _entity; };

      private:
        /// @brief Explicit constructor for the entity. This constructor can only be used in the registry.
        /// @param entity Number of the entity.
        explicit Entity(std::size_t entity) : _entity(entity){};

        /// @brief Entity number.
        std::size_t _entity;
    };
} // namespace GameEngine

#endif /* !ENTITY_HPP_ */
