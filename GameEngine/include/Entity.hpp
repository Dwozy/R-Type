/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_
    #include <cstdlib>

class Entity
{
    public:
        explicit Entity(std::size_t entity): _entity(entity) {};
        ~Entity() = default;

        operator std::size_t() const { return _entity; };
    private:
        std::size_t _entity;
};

#endif /* !ENTITY_HPP_ */
