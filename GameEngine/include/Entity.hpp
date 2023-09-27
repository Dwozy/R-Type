/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_
    #include <cstdlib>

class Registry;

class Entity
{
    public:
        friend class Registry;
        ~Entity() = default;

        operator std::size_t() const { return _entity; };
    private:
        explicit Entity(std::size_t entity): _entity(entity) {};

        std::size_t _entity;
};

#endif /* !ENTITY_HPP_ */
