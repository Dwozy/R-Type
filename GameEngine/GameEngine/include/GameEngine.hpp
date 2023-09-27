/*
** EPITECH PROJECT, 2023
** GameEngine.hpp
** File description:
** GameEngine
*/

#ifndef GAMEENGINE_HPP_
    #define GAMEENGINE_HPP_
    #include <memory>
    #include "Entity.hpp"
    #include "ComponentManager.hpp"
    #include "SystemManager.hpp"
    #include "DeltaTime.hpp"

namespace GameEngine
{
    class GameEngine
    {
        public:
            GameEngine(Entity maxEntities): _maxEntities(maxEntities)
            {
                _entityManager.reset(new EntityManager(_maxEntities));
                _componentManager.reset(new ComponentManager(_maxEntities));
            };
            ~GameEngine() = default;

            Entity createEntity() { return _entityManager->createEntity(); };
            void destroyEntity(Entity entity) { _entityManager->destroyEntity(entity); };
            void setEntitySignature(Entity entity, Signature signature) { _entityManager->setSignature(entity, signature); };
            const Signature &getSignature(Entity entity) const { return _entityManager->getSignature(entity); };

            template<typename CompType>
            void registerComponent() { _componentManager->registerComponent<CompType>(); };
            template<typename CompType>
            const ComponentId &getComponentId() { return _componentManager->getComponentId<CompType>(); };
            template<typename CompType>
            void assignComponent(Entity entity, CompType component) { _componentManager->assignComponent<CompType>(entity, component); };
            template<typename CompType>
            CompType &getComponent(Entity entity) { _componentManager->getComponent<CompType>(entity); };
            void entityDestroyed(Entity entity) { _componentManager->entityDestroyed(entity); };

            template<typename SysType>
            std::shared_ptr<SysType> registerSystem(){ return _systemManager.registerSystem<SysType>(*this); };
            template<typename SysType>
            std::shared_ptr<SysType> getSystem() { _systemManager.getSystem<SysType>(); };

            const float &getDeltaTime() const { return _deltaTime.getDeltaTime(); };
            void updateDeltaTime() { _deltaTime.update(); };

        private:
            std::shared_ptr<EntityManager> _entityManager;
            std::shared_ptr<ComponentManager> _componentManager;
            SystemManager _systemManager;
            Entity _maxEntities;
            DeltaTime _deltaTime;
    };
}

#endif /* !GAMEENGINE_HPP_ */
