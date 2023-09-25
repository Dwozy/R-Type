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
    #include <vector>
    #include "Component.hpp"
    #include "Error.hpp"

namespace GameEngine
{
    using Entity = std::uint32_t;

    using Signature = std::bitset<MAX_COMPONENT>;

    class EntityManager
    {
        public:
            EntityManager(Entity maxEntities);
            ~EntityManager() = default;

            Entity createEntity();
            void destroyEntity(Entity entity);

            void setSignature(Entity entity, Signature signature);
            const Signature &getSignature(Entity entity) const;

        private:
            std::vector<Entity> _entitiesAvailable;
            std::vector<Signature> _entitiesSignatures;
            Entity _nbEntity = 0;
            Entity _maxEntities;
    };
}

#endif /* !ENTITY_HPP_ */
