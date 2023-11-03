/*
** EPITECH PROJECT, 2023
** HandlingMove.cpp
** File description:
** HandlingMove
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::handleMove(struct RType::Protocol::MoveData moveInfo)
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        if (moveInfo.id > transforms.size())
            return;
        if (!transforms[moveInfo.id])
            return;
        if (moveInfo.dx == 0 && moveInfo.dy == 0)
            transforms[moveInfo.id]->position = {moveInfo.x, moveInfo.y};
        transforms[moveInfo.id]->velocity.x = moveInfo.dx;
        transforms[moveInfo.id]->velocity.y = moveInfo.dy;
        GameEngine::Entity entity = _gameEngine.registry.getEntityById(moveInfo.id);
        broadcastEntityInformation(entity);
    }
} // namespace RType::Server
