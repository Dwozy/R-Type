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
    // const Entity MAX_ENTITY = 1000;

    using Signature = std::bitset<MAX_COMPONENT>;

    class EntityManager
    {
        public:
            EntityManager(Entity maxEntities): _maxEntities(maxEntities)
            {
                _entitiesAvailable.reserve(maxEntities);
                _entitiesSignatures.reserve(maxEntities);
                for (Entity entity = 0; entity < _maxEntities; entity++)
                    _entitiesAvailable.push_back(entity);
            };
            ~EntityManager() = default;

            Entity createEntity()
            {
                Entity entity;

                if (_entitiesAvailable.empty())
                    throw Error::NoEntityAvailableError();
                entity = _entitiesAvailable.front();
                _entitiesAvailable.erase(_entitiesAvailable.begin());
                return entity;
            };
            void destroyEntity(Entity entity)
            {
                if (entity >= _maxEntities)
                    throw Error::OutOfEntitiesLimitError();

                _entitiesSignatures[entity].reset();
                _entitiesAvailable.push_back(entity);
            };

            void setSignature(Entity entity, Signature signature)
            {
                if (entity >= _maxEntities)
                    throw Error::OutOfEntitiesLimitError();

                _entitiesSignatures[entity] = signature;
            };
            const Signature &getSignature(Entity entity) const
            {
                if (entity >= _maxEntities)
                    throw Error::OutOfEntitiesLimitError();

                return _entitiesSignatures[entity];
            };

        private:
            std::vector<Entity> _entitiesAvailable;
            std::vector<Signature> _entitiesSignatures;
            Entity _nbEntity = 0;
            Entity _maxEntities;
    };
}

#endif /* !ENTITY_HPP_ */
