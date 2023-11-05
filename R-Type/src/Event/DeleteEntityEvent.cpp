/*
** EPITECH PROJECT, 2023
** DeleteEntityEvent.cpp
** File description:
** DeleteEntityEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::deleteEntity(struct RType::Protocol::EntityIdData entityId)
    {
        if (!searchEntity(entityId.id))
            return;
        std::size_t id = findEntity(entityId.id);
        GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
        if (entity == _id)
            _id = -1;
        _gameEngine.registry.killEntity(entity);
    }

    void RTypeClient::setDeleteEntityCallback()
    {
        auto &refHandlerDelete = _gameEngine.eventManager.addHandler<struct RType::Protocol::EntityIdData>(
            static_cast<GameEngine::EventType>(GameEngine::Event::DeleteEntity));
        auto handleDelete = std::bind(&RType::Client::RTypeClient::deleteEntity, this, std::placeholders::_1);
        refHandlerDelete.subscribe(handleDelete);
    }
} // namespace RType::Client
