/*
** EPITECH PROJECT, 2023
** UpdateEntityEvent.cpp
** File description:
** UpdateEntityEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::updateEntity(const struct rtype::Entity entity)
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        if (entity.id > transforms.size())
            return;
        if (!transforms[entity.id].has_value()) {
            GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity(entity.id);
            _entityManager.setPlayerEntity(entity, newEntity, _gameEngine.registry);
        } else {
            transforms[entity.id]->velocity.x = entity.directionX;
            transforms[entity.id]->velocity.y = entity.directionY;
            // transforms[entity.id]->position.x = (fabs(transforms[entity.id]->position.x - entity.positionX) < 2)
            //                                         ? transforms[entity.id]->position.x
            //                                         : entity.positionX;
            // transforms[entity.id]->position.y = (fabs(transforms[entity.id]->position.y - entity.positionY) < 2)
            //                                         ? transforms[entity.id]->position.y
            //                                         : entity.positionY;
            transforms[entity.id]->position.x = entity.positionX;
            transforms[entity.id]->position.y = entity.positionY;
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
