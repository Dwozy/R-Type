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
    /// @brief Number in uint32 with the ID of the entity. Used in the game engine with every managers.
    using Entity = std::uint32_t;

    /// @brief Bitset with the maximum of component it can handle. Each component have an ID, and if this ID is true in the bitset, the entity posseses this component.
    using Signature = std::bitset<MAX_COMPONENT>;

    /// @brief Entity manager class, which create and destroy entities and keep the signature of them.
    class EntityManager
    {
        public:
            /// @brief Constructor for the EntityManager.
            /// @param maxEntities Maximum of entity at once. Will be used to allocate the entities.
            EntityManager(Entity maxEntities);
            ~EntityManager() = default;

            /// @brief Creates an entity.
            /// @return The created entity.
            Entity createEntity();
            /// @brief Destroys the entity and resets the entity's signature.
            /// @param entity Entity to destroy.
            void destroyEntity(Entity entity);

            /// @brief Set a new signature () to the entity.
            /// @param entity Entity to set signature.
            /// @param signature Signature to set.
            void setSignature(Entity entity, Signature signature);
            /// @brief Getter for the entity's signature.
            /// @param entity Entity you want to get signature from.
            /// @return The entity's signature that can"t be modified. If you want to modify it, use setSignature instead.
            const Signature &getSignature(Entity entity) const;

        private:
            std::vector<Entity> _entitiesAvailable;
            std::vector<Signature> _entitiesSignatures;
            Entity _nbEntity = 0;
            Entity _maxEntities;
    };
}

#endif /* !ENTITY_HPP_ */
