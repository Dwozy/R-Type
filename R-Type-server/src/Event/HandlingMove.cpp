/*
** EPITECH PROJECT, 2023
** HandlingMove.cpp
** File description:
** HandlingMove
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::handleMove(struct rtype::Event event)
    {
        auto moveInfo = std::any_cast<RType::Protocol::MoveData>(event.data);
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        if (moveInfo.id > transforms.size())
            return;
        if (!transforms[moveInfo.id])
            return;
        transforms[moveInfo.id]->position = {moveInfo.x, moveInfo.y};
        transforms[moveInfo.id]->velocity.x = moveInfo.dx;
        transforms[moveInfo.id]->velocity.y = moveInfo.dy;
        GameEngine::Entity entity = _gameEngine.registry.getEntityById(moveInfo.id);
        broadcastEntityInformation(entity);
    }
} // namespace RType::Server
