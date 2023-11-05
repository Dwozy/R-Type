/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include <any>
#include <functional>
#include <string>
#include <typeindex>
#include <utility>
#include <algorithm>
#include "Entity.hpp"
#include "Error.hpp"
#include "SparseArray.hpp"

namespace Debug
{
    class DebugMenu;
}
#ifdef DEBUG
#endif

namespace GameEngine
{
    /// @brief Entity component system, handling entities, components and systems
    class Registry
    {
#ifdef DEBUG
#endif
        friend class Debug::DebugMenu;

      public:
        /// @brief Constructor
        /// @param maxEntities Maximum amount of entities at once. Will set the maximum size for the components array.
        Registry(const std::size_t maxEntities) : _maxEntities(maxEntities){};

        /// @brief Register a new component to the registry.
        /// @tparam Component type of the component to register
        /// @return A reference to the register component's SparseArray
        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            _container.insert({std::type_index(typeid(Component)), SparseArray<Component>()});
            SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container[std::type_index(typeid(Component))]);
            ret.resize(_maxEntities);
            std::function<void(Registry &, const Entity &)> deleter = [](Registry &registry, const Entity &entity) {
                registry.getComponent<Component>().erase(entity);
            };
            _deleters.push_back(deleter);
            return ret;
        };
        /// @brief Getter to a speecific component's SparseArray
        /// @tparam Component type of the component to get
        /// @return A reference to the component's SparseArray
        template <class Component>
        SparseArray<Component> &getComponent()
        {
            SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container[std::type_index(typeid(Component))]);
            return ret;
        };
        /// @brief Getter to a speecific component's SparseArray
        /// @tparam Component type of the component to get
        /// @return A constant reference to the component's SparseArray
        template <class Component>
        const SparseArray<Component> &getComponent() const
        {
            const SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container.at(std::type_index(typeid(Component))));
            return ret;
        };

        /// @brief Spawns a new entity. Entities can't be spawned otherwise.
        /// @return The spawned entity.
        Entity spawnEntity()
        {
            std::size_t id;

            if (!_emptyIndexes.empty()) {
                id = _emptyIndexes.front();
                _emptyIndexes.erase(_emptyIndexes.begin());
                return Entity(id);
            }
            if (_nbEntities > _maxEntities)
                throw Error::TooMuchEntitiesError();
            id = _nbEntities;
            _nbEntities++;
            return Entity(id);
        };
        /// @brief Spawns a new entity. Entities can't be spawned otherwise.
        /// @param id Id of the entity to spawn.
        /// @return The spawned entity.
        Entity spawnEntity(const std::size_t &id)
        {
            if (id > _maxEntities)
                throw Error::InvalidEntityIdError();
            if (!_emptyIndexes.empty()) {
                auto it = std::lower_bound(_emptyIndexes.begin(), _emptyIndexes.end(), id);
                if (it != _emptyIndexes.end())
                    _emptyIndexes.erase(it);
                return Entity(id);
            }
            for (; _nbEntities != id; _nbEntities++)
                _emptyIndexes.push_back(_nbEntities);
            std::sort(_emptyIndexes.begin(), _emptyIndexes.end());
            _nbEntities++;
            return Entity(id);
        };
        /// @brief Getter for an entity at a given index. Will throw an error if the entity hasn't been spawned.
        /// @param id Index of the entity.
        /// @return The entity at the given index.
        Entity getEntityById(const std::size_t &id) const
        {
            if (id > _nbEntities || id > _maxEntities)
                throw Error::InvalidEntityIdError();
            if (std::binary_search(_emptyIndexes.begin(), _emptyIndexes.end(), id))
                throw Error::InvalidEntityIdError();
            return Entity(id);
        };
        /// @brief Kills the entity given, it destroys all the components to this entity.
        /// @param entity Entity to kill.
        void killEntity(const Entity &entity)
        {
            _emptyIndexes.push_back(entity);
            std::sort(_emptyIndexes.begin(), _emptyIndexes.end());
            for (std::size_t i = 0; i < _deleters.size(); i++)
                _deleters[i](*this, entity);
        };

        /// @brief Add a component to the entity given.
        /// @tparam Component type of the component to add to the entity.
        /// @param entity Entity on which the component will be added.
        /// @param component Component to add to the entity. The component will be moved.
        /// @return A reference to the component.
        template <typename Component>
        typename SparseArray<Component>::referenceType addComponent(const Entity &entity, Component &&component)
        {
            return getComponent<Component>().insert_at(entity, component);
        };
        /// @brief Add a component to the entity given.
        /// @tparam Component type of the component to add to the entity.
        /// @param entity Entity on which the component will be added.
        /// @param component Component to add to the entity. The component will be copied.
        /// @return A reference to the component.
        template <typename Component>
        typename SparseArray<Component>::referenceType addComponent(const Entity &entity, const Component &component)
        {
            return getComponent<Component>().insert_at(entity, component);
        };
        /// @brief Emplace the component type to the entities given.
        /// @tparam Component type of the component to emplace to the entities.
        /// @tparam ...Params Variadic parameters of Entities to emplace the component to.
        /// @param entity First entity to emplace.
        /// @param ...params Variadic parameter of entities.
        /// @return A reference to the component of the first entity.
        template <typename Component, typename... Params>
        typename SparseArray<Component>::referenceType emplaceComponent(const Entity &entity, Params &&...params)
        {
            return getComponent<Component>().emplace_at(entity, params...);
        };
        /// @brief Removes a component to the specified entity.
        /// @tparam Component type of the component to remove.
        /// @param entity Entity to remove the component from.
        template <typename Component>
        void removeComponent(const Entity &entity)
        {
            getComponent<Component>().erase(entity);
        };
        /// @brief tells if a component is registered
        /// @tparam Component component to find
        /// @return boolean indicating whether the component is registered
        template <typename Component>
        bool isComponentRegistered()
        {
            if (_container.find(std::type_index(typeid(Component))) != _container.end())
                return true;
            return false;
        };

        /// @brief Adds a system to the registry. The system function can take reference to some component's
        /// SparseArrays, they will be automatically get.
        /// @tparam Function type of the system function to registeru
        /// @tparam ...Components Variadic template for the components which are in parameter of the system function.
        /// @param function System function to register.
        template <typename Function, class... Components>
        void addSystem(const Function &function)
        {
            std::function<void()> system = [this, function]() { function(getComponent<Components>()...); };

            _systems.push_back(system);
        };
        /// @brief Adds a system to the registry. This method is to use when the class system needs to stay at the same
        /// place in the memory (for example DrawSystem)
        /// @tparam SystemClass Class of the system to register, must have an overload for the ()
        /// @tparam ...Components Variadic template for the components which are in parameter of the system function.
        /// @param systemClass System class to register.
        template <typename SystemClass, class... Components>
        void addSystem(std::shared_ptr<SystemClass> systemClass)
        {
            std::function<void()> system = [this, systemClass]() mutable {
                (*systemClass)(getComponent<Components>()...);
            };

            _systems.push_back(system);
        };
        /// @brief Runs all the registered system functions. Need to be called in the main loop.
        void runSystems()
        {
            for (std::size_t i = 0; i < _systems.size(); i++)
                _systems[i]();
        }

        /// @brief Return max entities
        /// @return _maxEntities;
        std::size_t getMaxEntities()
        {
            return _maxEntities;
        }

      private:
        /// @brief Unordered map storing all the component's SparseArray.
        std::unordered_map<std::type_index, std::any> _container;
        /// @brief Deleters functions for a specific entity in a SparseArray. Will be called when an entity is killed.
        std::vector<std::function<void(Registry &, const Entity &)>> _deleters;
        /// @brief Vector storing all the system functions.
        std::vector<std::function<void()>> _systems;
        /// @brief Vector storing the killed entities to reassign their index when spawning an entity.
        std::vector<std::size_t> _emptyIndexes;
        /// @brief Maximum number of entities at once.
        std::size_t _maxEntities;
        /// @brief Current number of entities.
        std::size_t _nbEntities = 0;
    };
} // namespace GameEngine

#endif /* !REGISTRY_HPP_ */
