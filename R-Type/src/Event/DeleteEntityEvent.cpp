/*
** EPITECH PROJECT, 2023
** DeleteEntityEvent.cpp
** File description:
** DeleteEntityEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::deleteEntity(const struct rtype::EntityId entityId)
    {
        if (entityId.id == 0)
            return;
        struct GameEngine::Entity entity = _gameEngine.registry.getEntityById(entityId.id);
        _gameEngine.registry.killEntity(entity);
        std::cout << "Player " << _id << " got : Player : " << entityId.id << " died." << std::endl;
    }

    void RTypeClient::setDeleteEntityCallback()
    {
        auto &refHandlerDelete =
            _gameEngine.eventManager.addHandler<struct rtype::EntityId>(GameEngine::Event::DeleteEntity);
        auto handleDelete = std::bind(&RType::Client::RTypeClient::deleteEntity, this, std::placeholders::_1);
        refHandlerDelete.subscribe(handleDelete);
    }
} // namespace RType::Client