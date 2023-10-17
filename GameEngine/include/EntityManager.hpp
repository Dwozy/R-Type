/*
** EPITECH PROJECT, 2023
** EntityManager.hpp
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "Registry.hpp"

namespace GameEngine
{

    class EntityManager
    {
      public:
        void setPlayerEntity(float posX, float posY, Entity entity, Registry &registry);
        void setEntity(float posX, float posY, Entity entity, Registry &registry);
        void setControlPlayerEntity(Entity entity, Registry &registry);

      protected:
      private:
    };
} // namespace GameEngine

#endif /* !ENTITYMANAGER_HPP_ */
