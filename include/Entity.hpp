/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_
    #include <cstdint>
    #include <bitset>
    #include <array>
    #include <queue>
    #include "Component.hpp"
    #include "Error.hpp"

namespace GameEngine
{
    using Entity = std::uint32_t;
    const Entity MAX_ENTITY = 1000;

    using Signature = std::bitset<MAX_COMPONENT>;

    class EntityManager
    {
        public:
            EntityManager();
            ~EntityManager() = default;

            Entity createEntity();
            void destroyEntity(Entity entity);

            void setSignature(Entity entity, Signature signature);
            Signature getSignature(Entity entity);

        private:
            std::queue<Entity> _entitiesAvailable;
            std::array<Signature, MAX_ENTITY> _entitiesSignatures;
            Entity _nbEntity = 0;
    };
}

#endif /* !ENTITY_HPP_ */
