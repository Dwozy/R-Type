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
            EntityManager()
            {
                for (Entity entity = 0; entity < MAX_ENTITY; entity++)
                    _entitiesAvailable.push(entity);
            };

            ~EntityManager() = default;

            Entity createEntity()
            {
                Entity entity;

                if (_entitiesAvailable.empty())
                    throw Error::NoEntityAvailableError();
                entity = _entitiesAvailable.front();
                _entitiesAvailable.pop();
                return entity;
            };

            void destroyEntity(Entity entity)
            {
                if (entity >= MAX_ENTITY)
                    throw Error::OutOfEntitiesLimit();

                // reset signature
                _entitiesAvailable.push(entity);
            }

            // manage signatures

        private:
            std::queue<Entity> _entitiesAvailable;
            std::array<Signature, MAX_ENTITY> _entitiesSignatures;
            Entity _nbEntity = 0;
    };
}

#endif /* !ENTITY_HPP_ */
