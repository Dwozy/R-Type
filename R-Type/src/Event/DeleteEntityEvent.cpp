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
        if (!_searchEntity(entityId.id))
            return;
        std::size_t id = _findEntity(entityId.id);
        GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
        if (entity == _id) {
            std::cout << "Delete player : " << _id << std::endl;
            _isAlive = false;
            _id = -1;
        }
        _gameEngine.registry.killEntity(entity);
    }

    void RTypeClient::setDeleteEntityCallback()
    {
        auto &refHandlerDelete =
            _gameEngine.eventManager.addHandler<struct rtype::EntityId>(GameEngine::Event::DeleteEntity);
        auto handleDelete = std::bind(&RType::Client::RTypeClient::deleteEntity, this, std::placeholders::_1);
        refHandlerDelete.subscribe(handleDelete);
    }
} // namespace RType::Client
