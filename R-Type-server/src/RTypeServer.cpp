/*
** EPITECH PROJECT, 2023
** RTypeServer.cpp
** File description:
** RTypeServer
*/

#include "RTypeServer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"

void test(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms)
{
    auto &selfCol = collisions[entityId];
    auto &selfTsf = transforms[entityId];

    if (!selfCol || !selfTsf)
        return;
    for (std::size_t i = 0; i < collisions.size(); i++) {
        if (i == entityId)
            continue;
        auto &col = collisions[i];
        auto &tsf = transforms[i];

        if (!col || !tsf || !col.value().isActive)
            continue;
        selfCol.value().collider.handleCollisionFromRect(
            selfTsf.value().position, col.value().collider, tsf.value().position);
    }
}

RType::Server::RTypeServer::RTypeServer(unsigned short port)
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue))
{
    // std::thread run([this](){_IOContext.run();});
    gameLoop();
    run.join();
    // gameLoop();
}

void RType::Server::RTypeServer::handleEvent()
{
    struct rtype::Event event;

    while (!_eventQueue.size() != 0) {
        event = _eventQueue.pop();
        switch (event.packetType) {
            case static_cast<uint8_t> (rtype::PacketType::CONNEXION):
                break;
            case static_cast<uint8_t> (rtype::PacketType::MOVE):
                break;
        }
    }
}

RType::Server::RTypeServer::~RTypeServer() {}

void RType::Server::RTypeServer::gameLoop()
{
    while (!_IOContext.stopped()) {
        if (!_eventQueue.size() != 0)
            handleEvent();
        // _IOContext.run_one();
    }
}
