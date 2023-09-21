/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentArray
*/

#ifndef COMPONENTARRAY_HPP_
    #define COMPONENTARRAY_HPP_
    #include <set>
    #include "Entity.hpp"
    #include "Error.hpp"

namespace GameEngine
{
    class IComponentArray
    {
        public:
            virtual ~IComponentArray() = default;
            virtual void entityDestroyed(Entity entity) = 0;
    };

    template<typename CompType>
    class ComponentArray : public IComponentArray
    {
        public:
            void asignComponent(Entity entity, CompType component)
            {
                if (_assignedEntity.find(entity) != _assignedEntity.end())
                    throw Error::ComponentAlreadyAssiggnedError();

                _componentArray[entity] = component;
                _asignedEntites.insert(entity);
            };

            void removeComponent(Entity entity)
            {
                if (_assignedEntity.find(entity) == _assignedEntity.end())
                    throw Error::ComponentNotAsignedError();

                _asignedEntites.erase(entity);
            };

            CompType &getComponent(Entity entity)
            {
                if (_assignedEntity.find(entity) == _assignedEntity.end())
                    throw Error::ComponentNotAsignedError();

                return _componentArray[entity];
            };

            void entityDestroyed(Entity entity) override
            {
                if (_assignedEntity.find(entity) != _assignedEntity.end())
                    removeComponent(entity);
            };

        private:
            std::array<CompType, MAX_ENTITY> _componentArray;
            std::set<Entity> _asignedEntites;
    };
}

#endif /* !COMPONENTARRAY_HPP_ */
