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
#include <algorithm>
#include <any>
#include <functional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace GameEngine
{
    class GameEngine;

    class Registry
    {
      public:
        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            _container.insert({std::type_index(typeid(Component)), SparseArray<Component>()});
            SparseArray<Component> &ret =
                std::any_cast<SparseArray<Component> &>(_container[std::type_index(typeid(Component))]);
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

            if (!_emptyIndecies.empty()) {
                id = _emptyIndecies.back();
                _emptyIndecies.pop_back();
                _aliveEntities.insert(_aliveEntities.begin() + id, Entity(id));
                return _aliveEntities[id];
            }
            id = _aliveEntities.size();
            _aliveEntities.push_back(Entity(id));
            return _aliveEntities.back();
        };
        Entity entityFromIndex(std::size_t idx) { return _aliveEntities[idx]; };
        void killEntity(const Entity &entity)
        {
            auto idx = std::lower_bound(_aliveEntities.begin(), _aliveEntities.end(), entity);

            Entity id = *idx;
            _emptyIndecies.push_back(id);
            _aliveEntities.erase(idx);
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
        void addSystem(const Function &function, GameEngine &gameEngine)
        {
            std::function<void()> system = [this, &gameEngine, function]() {
                function(gameEngine, getComponent<Components>()...);
            };

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
        std::vector<Entity> _aliveEntities;
        std::vector<std::size_t> _emptyIndecies;
        std::vector<std::function<void()>> _systems;
    };
} // namespace GameEngine

#endif /* !REGISTRY_HPP_ */
