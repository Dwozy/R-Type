/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_
#include "Entity.hpp"

namespace GameEngine
{
    class IScene
    {
      public:
        virtual ~IScene() = default;

        virtual void load() = 0;
        virtual void unload() = 0;
        virtual void addEntityToUnload(Entity entity) = 0;
    };
} // namespace GameEngine

#endif /* !ISCENE_HPP_ */
