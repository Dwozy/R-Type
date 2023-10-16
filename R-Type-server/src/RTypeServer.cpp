/*
** EPITECH PROJECT, 2023
** RTypeServer.cpp
** File description:
** RTypeServer
*/

#include "RTypeServer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"

RType::Server::RTypeServer::RTypeServer(unsigned short port)
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue))
{
    _gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
    _gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();

    _gameEngine.registry.spawnEntity();

    pos = 1;
    _isRunning = true;
    std::thread network(&RType::Server::RTypeServer::startNetwork, this, std::ref(_isRunning));
    network.detach();
    gameLoop();
}

RType::Server::RTypeServer::~RTypeServer() {}

void RType::Server::RTypeServer::startNetwork(bool &isRunning)
{
    _signal.async_wait(std::bind(&asio::io_context::stop, &_IOContext));
    _udpServer.run();
    _IOContext.run();
    isRunning = false;
}

void RType::Server::RTypeServer::handleConnexion()
{
    GameEngine::Entity entity = _gameEngine.registry.spawnEntity();

    std::cout << "Spawn Entity" << std::endl;
    _entityManager.setEntity(pos * 25, pos * 25, entity, _gameEngine.registry);
    struct rtype::Entity newEntity = {.id = static_cast<uint16_t> (pos),
        .positionX = static_cast<uint32_t>(pos * 25),
        .positionY = static_cast<uint32_t>(pos * 25),
        .directionX = 0,
        .directionY = 0};
    _listEntities.push_back(entity);
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(newEntity);
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::CONNECTED), dataToSend);
    std::cout << "Message when new connexion" << std::endl;
    pos++;
}

void RType::Server::RTypeServer::handleMove(struct rtype::Event event)
{
    struct rtype::Move moveInfo = std::any_cast<struct rtype::Move>(event.data);

    auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

    if (moveInfo.id > transforms.size())
        throw;
    transforms[moveInfo.id]->velocity.x = moveInfo.directionX;
    transforms[moveInfo.id]->velocity.y = moveInfo.directionY;
    struct rtype::Entity entity = {.id = static_cast<uint16_t>(moveInfo.id),
        .positionX = static_cast<uint32_t>(transforms[moveInfo.id]->position.x),
        .positionY = static_cast<uint32_t>(transforms[moveInfo.id]->position.y),
        .directionX = transforms[moveInfo.id]->velocity.x,
        .directionY = transforms[moveInfo.id]->velocity.y};
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity);
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
}

void RType::Server::RTypeServer::handleEvent()
{
    struct rtype::Event event;

    while (_eventQueue.size() != 0) {
        event = _eventQueue.pop();
        switch (event.packetType) {
        case static_cast<uint8_t>(rtype::PacketType::CONNEXION):
            handleConnexion();
            break;
        case static_cast<uint8_t>(rtype::PacketType::MOVE):
            handleMove(event);
            break;
        }
    }
}

void RType::Server::RTypeServer::updateEntities()
{
    auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

    for (std::size_t i = 0; i < transforms.size(); i++) {
        auto &transform = transforms[i];
        if (!transform.has_value())
            continue;
        struct rtype::Entity entity = {.id = static_cast<uint16_t>(i),
            .positionX = static_cast<uint32_t>(transform->position.x),
            .positionY = static_cast<uint32_t>(transform->position.y),
            .directionX = transform->velocity.x,
            .directionY = transform->velocity.y};
        std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity);
        _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
    }
}

void RType::Server::RTypeServer::gameLoop()
{
    std::chrono::steady_clock::time_point _lastTime;
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    _lastTime = now;

    while (_isRunning) {
        now = std::chrono::steady_clock::now();
        auto _deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTime);
        if (_eventQueue.size() != 0)
            handleEvent();
        if (_deltaTime.count() > 0.1) {
            updateEntities();
            _lastTime = now;
        }
    }
}
