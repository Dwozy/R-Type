/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include "Entity.hpp"
#include "Error.hpp"
#include "SparseArray.hpp"
#include "Error.hpp"
#include <algorithm>
#include <any>
#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <iostream>

namespace GameEngine
{
    class Registry
    {
      public:
        Registry(const std::size_t maxEntities) : _maxEntities(maxEntities){};

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
        template <class Component>
        SparseArray<Component> &getComponent()
        {
            SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container[std::type_index(typeid(Component))]);
            return ret;
        };
        template <class Component>
        const SparseArray<Component> &getComponent() const
        {
            const SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container.at(std::type_index(typeid(Component))));
            return ret;
        };

        Entity spawnEntity()
        {
            std::size_t id;

            if (!_emptyIndexes.empty()) {
                id = _emptyIndexes.back();
                _emptyIndexes.pop_back();
                return Entity(id);
            }
            if (_nbEntities > _maxEntities)
                throw Error::TooMuchEntitiesError();
            id = _nbEntities;
            _nbEntities++;
            return Entity(id);
        };
        Entity spawnEntity(const std::size_t &id)
        {
            if (id > _maxEntities)
                throw;
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
        Entity getEntityById(const std::size_t &id) const
        {
            if (id > _nbEntities || id > _maxEntities)
                throw;
            if (std::binary_search(_emptyIndexes.begin(), _emptyIndexes.end(), id))
                throw;
            return Entity(id);
        };
        void killEntity(const Entity &entity)
        {
            _emptyIndexes.push_back(entity);
            std::sort(_emptyIndexes.begin(), _emptyIndexes.end());
            for (std::size_t i = 0; i < _deleters.size(); i++)
                _deleters[i](*this, entity);
        };

        template <typename Component>
        typename SparseArray<Component>::referenceType addComponent(const Entity &entity, Component &&component)
        {
            return getComponent<Component>().insert_at(entity, component);
        };
        template <typename Component>
        typename SparseArray<Component>::referenceType addComponent(const Entity &entity, const Component &component)
        {
            return getComponent<Component>().insert_at(entity, component);
        };
        template <typename Component, typename... Params>
        typename SparseArray<Component>::referenceType emplaceComponent(const Entity &entity, Params &&...params)
        {
            return getComponent<Component>().emplace_at(entity, params...);
        };
        template <typename Component>
        void removeComponent(const Entity &entity)
        {
            getComponent<Component>().erase(entity);
        };

        template <typename Function, class... Components>
        void addSystem(const Function &function)
        {
            std::function<void()> system = [this, function]() { function(getComponent<Components>()...); };

            _systems.push_back(system);
        };
        void runSystems()
        {
            for (std::size_t i = 0; i < _systems.size(); i++)
                _systems[i]();
        }

      private:
        std::unordered_map<std::type_index, std::any> _container;
        std::vector<std::function<void(Registry &, const Entity &)>> _deleters;
        std::vector<std::size_t> _emptyIndexes;
        std::vector<std::function<void()>> _systems;
        std::size_t _maxEntities;
        std::size_t _nbEntities = 0;
    };
} // namespace GameEngine

#endif /* !REGISTRY_HPP_ */
