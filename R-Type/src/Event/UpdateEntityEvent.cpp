/*
** EPITECH PROJECT, 2023
** UpdateEntityEvent.cpp
** File description:
** UpdateEntityEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::updateEntity(const struct rtype::Entity entity)
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        if (!_searchEntity(entity.id)) {
            GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                newEntity, GameEngine::NetworkIdComponent{entity.id});
            _entityManager.setEntityFromClient(entity, newEntity, _gameEngine.registry);
            return;
        }
        std::size_t id = _findEntity(entity.id);
        if (!transforms[id].has_value()) {
            GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                newEntity, GameEngine::NetworkIdComponent{entity.id});
            _entityManager.setEntityFromClient(entity, newEntity, _gameEngine.registry);
        } else {
            transforms[id]->velocity.x = entity.directionX;
            transforms[id]->velocity.y = entity.directionY;
            transforms[id]->position.x = (fabs(transforms[id]->position.x - entity.positionX) < 2)
                                             ? transforms[id]->position.x
                                             : entity.positionX;
            transforms[id]->position.y = (fabs(transforms[id]->position.y - entity.positionY) < 2)
                                             ? transforms[id]->position.y
                                             : entity.positionY;
        }
    }

    void RTypeClient::setUpdateEntityCallback()
    {
        auto &refHandlerUpdate =
            _gameEngine.eventManager.addHandler<struct rtype::Entity>(GameEngine::Event::GetEntity);
        auto handleUpdate = std::bind(&RType::Client::RTypeClient::updateEntity, this, std::placeholders::_1);
        refHandlerUpdate.subscribe(handleUpdate);
    }
} // namespace RType::Client
