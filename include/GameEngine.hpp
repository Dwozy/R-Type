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
    /// @brief GameEngine class which handles the game
    class GameEngine
    {
        public:
            /// @brief Constructor of GameEngine class
            /// @param maxEntities Maximum of entities at one time, this will alocate the memory for all the entities
            GameEngine(Entity maxEntities): _maxEntities(maxEntities)
            {
                _entityManager.reset(new EntityManager(_maxEntities));
                _componentManager.reset(new ComponentManager(_maxEntities));
                updateDeltaTime();
            };
            ~GameEngine() = default;

            /// @brief Create an entity with the EntityManager
            /// @return The created entity
            Entity createEntity() { return _entityManager->createEntity(); };
            /// @brief Destroy the entity by puting it back in the available entities in the EntityManager. It also remove it from the components and systems.
            /// @param entity Entity to destroy.
            void destroyEntity(Entity entity);
            /// @brief Set a new signature () to the entity.
            /// @param entity Entity to set signature.
            /// @param signature Signature to set.
            void setEntitySignature(Entity entity, Signature signature) { _entityManager->setSignature(entity, signature); };
            /// @brief Getter for the entity's signature.
            /// @param entity Entity you want to get signature from.
            /// @return The entity's signature that can"t be modified. If you want to modify it, use setSignature instead.
            const Signature &getSignature(Entity entity) const { return _entityManager->getSignature(entity); };

            /// @brief Register a new component in the component manager.
            /// @tparam CompType Type of the component to register.
            template<typename CompType>
            void registerComponent() { _componentManager->registerComponent<CompType>(); };
            /// @brief Getter for the component ID.
            /// @tparam CompType Type of the component you want to get his ID from.
            /// @return The ID of the component.
            template<typename CompType>
            const ComponentId &getComponentId() { return _componentManager->getComponentId<CompType>(); };
            /// @brief Assigns an entity to a component. The component need to be registered before.
            /// @tparam CompType Type of the component.
            /// @param entity Entity to which the component will be assigned to.
            /// @param component Default value of the component.
            template<typename CompType>
            void assignComponent(Entity entity, CompType component) { _componentManager->assignComponent<CompType>(entity, component); };
            /// @brief Getter to an entity's component.
            /// @tparam CompType Type of the component.
            /// @param entity Entity from which you want to get the component.
            /// @return A reference to the entity's component.
            template<typename CompType>
            CompType &getComponent(Entity entity) { _componentManager->getComponent<CompType>(entity); };

            /// @brief Registers a new system in the system manager.
            /// @tparam SysType Type of the system to assign.
            /// @return A shared pointer to the system.
            template<typename SysType>
            std::shared_ptr<SysType> registerSystem(){ return _systemManager.registerSystem<SysType>(*this); };
            /// @brief Getter to a system.
            /// @tparam SysType Type of the system to get.
            /// @return A shared pointer to the system.
            template<typename SysType>
            std::shared_ptr<SysType> getSystem() { _systemManager.getSystem<SysType>(); };
            /// @brief Assigns an entity to a system.
            /// @tparam SysType Type of the system to assign the entity.
            /// @param entity Entity to assign.
            template<typename SysType>
            void assignSystem(Entity entity) { _systemManager.assignSystem<SysType>(entity); };

            /// @brief Getter for the deltaTime.
            /// @return A constant float of the delta time.
            const float &getDeltaTime() const { return _deltaTime.getDeltaTime(); };
            /// @brief Updates the delta time. This function should be called at the begining of every loop.
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
