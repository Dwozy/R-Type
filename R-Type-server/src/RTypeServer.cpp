/*
** EPITECH PROJECT, 2023
** RTypeServer.cpp
** File description:
** RTypeServer
*/

#include "Protocol.hpp"
#include "RTypeServer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "RType.hpp"

RType::Server::RTypeServer::RTypeServer(unsigned short port)
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue))
{
    _gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
    _gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();

    _gameEngine.registry.spawnEntity();
    // _gameEngine.registry.addSystem

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

    _entityManager.setEntity(entity * 25, entity * 25, entity, _gameEngine.registry);
    struct rtype::Entity newEntity = {.id = static_cast<uint16_t>(entity),
        .positionX = static_cast<float>(entity * 25),
        .positionY = static_cast<float>(entity * 25),
        .directionX = 0,
        .directionY = 0};
    std::cout << "Player " << entity << " spawned !" << std::endl;
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(newEntity);
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::CONNECTED), dataToSend);
}

void RType::Server::RTypeServer::handleMove(struct rtype::Event event)
{
    auto moveInfo = std::any_cast<RType::Protocol::MoveData>(event.data);

    auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

    if (moveInfo.id > transforms.size())
        return;
    transforms[moveInfo.id]->position = {moveInfo.x, moveInfo.y};
    transforms[moveInfo.id]->velocity.x = moveInfo.dx;
    transforms[moveInfo.id]->velocity.y = moveInfo.dy;
    struct rtype::Entity entity = {.id = static_cast<uint16_t>(moveInfo.id),
        .positionX = transforms[moveInfo.id]->position.x,
        .positionY = transforms[moveInfo.id]->position.y,
        .directionX = transforms[moveInfo.id]->velocity.x,
        .directionY = transforms[moveInfo.id]->velocity.y};
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity);
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
}

void RType::Server::RTypeServer::handleDisconnexion(struct rtype::Event event)
{
    struct rtype::EntityId entity = std::any_cast<struct rtype::EntityId>(event.data);
    auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

    if (entity.id > transforms.size())
        return;
    std::cout << "Player " << entity.id << " has to die !" << std::endl;
    GameEngine::Entity getEntity = _gameEngine.registry.getEntityById(entity.id);
    _gameEngine.registry.killEntity(getEntity);
    std::cout << "Player " << getEntity << " died !" << std::endl;
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::EntityId>(entity);
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::DISCONNEXION), dataToSend);
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
        case static_cast<uint8_t>(rtype::PacketType::DISCONNEXION):
            handleDisconnexion(event);
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
            .positionX = transform->position.x,
            .positionY = transform->position.y,
            .directionX = transform->velocity.x,
            .directionY = transform->velocity.y};
        std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity);
        _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
    }
}

void RType::Server::RTypeServer::gameLoop()
{
    while (_isRunning) {
        _gameEngine.deltaTime.update();
        if (_eventQueue.size() != 0)
            handleEvent();
        for (auto &transform : _gameEngine.registry.getComponent<GameEngine::TransformComponent>()) {
            if (!transform.has_value())
                continue;
            transform->position += transform->velocity * _gameEngine.deltaTime.getDeltaTime() * rtype::PLAYER_SPEED;
        }
        if (_gameEngine.deltaTime.getDeltaTime() > 0.2) {
            updateEntities();
        }
    }
}
