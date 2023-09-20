/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
    #define COMPONENTMANAGER_HPP_
    #include <unordered_map>
    #include <string>
    #include <memory>
    #include <typeinfo>
    #include "ComponentArray.hpp"
    #include "Error.hpp"

namespace GameEngine
{
    class ComponentManager {
        public:
            ~ComponentManager() = default;

            template<typename CompType>
            void registerComponent()
            {
                std::string typeId(typeid(CompType).name());

                if (_componentIds.find(typeId) != _componentIds.end())
                    throw Error::ComponentAlreadyRegisterError();
                _componentIds.insert({ typeId, _nbComponents });
                _components.insert({ typeId, make_shared<ComponentArray<CompType>>() });
            };

            template<typename CompType>
            ComponentId getComponentId()
            {
                std::string typeId(typeid(CompType).name());

                if (_componentIds.find(typeId) == _componentIds.end())
                    throw Error::ComponentNotRegisterError();

                return _componentIds[typeId];
            };

            template<typename CompType>
            void assignComponent(Entity entity, CompType component)
            {
                std::shared_ptr<ComponentArray<CompType>> componentArray = _getComponentArray<CompType>();

                componentArray->assignComponent(entity, component);
            };

            template<typename CompType>
            void removeComponent(Entity entity)
            {
                std::shared_ptr<ComponentArray<CompType>> componentArray = _getComponentArray<CompType>();

                componentArray->removeComponent(entity);
            }

            template<typename CompType>
            CompType &getComponent(Entity entity)
            {
                std::shared_ptr<ComponentArray<CompType>> componentArray = _getComponentArray<CompType>();

                componentArray->getComponent(entity);
            }

            void entityDestroyed(Entity entity)
            {
                for (auto component : _components)
                    component.second->entityDestroyed(entity);
            }

        private:
            template<typename CompType>
            std::shared_ptr<ComponentArray<CompType>> _getComponentArray()
            {
                std::string typeId(typeid(CompType).name());
                std::shared_ptr<ComponentArray<CompType>> component;

                if (_componentIds.find(typeId) == _componentIds.end())
                    throw Error::ComponentNotRegisterError();

                component = std::static_pointer_cast<ComponentArray<CompType>>(_components[typeId]);
                return component;
            };

            std::unordered_map<std::string, std::shared_ptr<IComponentArray>> _components;
            std::unordered_map<std::string, ComponentId> _componentIds;
            ComponentId _nbComponents = 0;
    };
}

#endif /* !COMPONENTMANAGER_HPP_ */
