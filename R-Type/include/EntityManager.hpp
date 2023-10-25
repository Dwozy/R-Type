/*
** EPITECH PROJECT, 2023
** EntityManager.hpp
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "RType.hpp"
#include "Registry.hpp"

namespace GameEngine
{
    class EntityManager
    {
      public:
        /// @brief Set the component adapted for the player entity
        /// @param posX position x of the player
        /// @param posY position y of the player
        /// @param entity that will be attribute the player components
        /// @param registry game engine registry that will set the components
        void setPlayerEntity(struct rtype::Entity entityInfo, Entity entity, Registry &registry);
        /// @brief Set the component adapted for a entity
        /// @param posX position x of the entity
        /// @param posY position y of the entity
        /// @param entity that will be attribute the player components
        /// @param registry game engine registry that will set the components
        void setEntity(struct rtype::Entity entityInfo, Entity entity, Registry &registry);
        /// @brief Set the component controller for the entity
        /// @param entity that will be attribute the controller component
        /// @param registry game engine registry that will set the components
        void setControlPlayerEntity(Entity entity, Registry &registry);

      protected:
      private:
    };
} // namespace GameEngine

#endif /* !ENTITYMANAGER_HPP_ */
