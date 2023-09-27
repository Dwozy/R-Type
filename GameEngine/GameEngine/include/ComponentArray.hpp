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
            ComponentArray(Entity maxEntities)
            {
                _componentArray.reserve(maxEntities);
            };

            void asignComponent(Entity entity, CompType component)
            {
                if (_assignedEntities.find(entity) != _assignedEntities.end())
                    throw Error::ComponentAlreadyAssignedError();

                _componentArray[entity] = component;
                _assignedEntities.insert(entity);
            };

            void removeComponent(Entity entity)
            {
                if (_assignedEntities.find(entity) == _assignedEntities.end())
                    throw Error::ComponentNotAsignedError();

                _assignedEntities.erase(entity);
            };

            CompType &getComponent(Entity entity)
            {
                if (_assignedEntities.find(entity) == _assignedEntities.end())
                    throw Error::ComponentNotAsignedError();

                return _componentArray[entity];
            };

            void entityDestroyed(Entity entity) override
            {
                if (_assignedEntities.find(entity) != _assignedEntities.end())
                    removeComponent(entity);
            };

        private:
            std::vector<CompType> _componentArray;
            std::set<Entity> _assignedEntities;
    };
}

#endif /* !COMPONENTARRAY_HPP_ */
