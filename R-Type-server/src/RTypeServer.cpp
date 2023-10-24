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
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue)),
      _tcpServer(_IOContext, port)
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
    _tcpServer.run();
    _udpServer.run();
    _IOContext.run();
    isRunning = false;
}

void RType::Server::RTypeServer::handleConnexion()
{
    GameEngine::Entity entity = _gameEngine.registry.spawnEntity();

    struct rtype::Entity newEntity = {.id = static_cast<uint16_t>(entity),
        .idTexture = static_cast<uint8_t> (rtype::TextureType::PLAYER),
        .positionX = static_cast<float>(entity * 25),
        .positionY = static_cast<float>(entity * 25),
        .directionX = 0,
        .directionY = 0};
    _entityManager.setEntity(newEntity, entity, _gameEngine.registry);
    std::cout << "Player " << entity << " spawned !" << std::endl;
    std::vector<std::byte> dataToSend =
        Serialization::serializeData<struct rtype::Entity>(newEntity, sizeof(newEntity));
    std::cout << "Has to send " << dataToSend.size() << std::endl;
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::CONNECTED), dataToSend);
}

void RType::Server::RTypeServer::handleShoot(struct rtype::Event event)
{
    auto shootInfo = std::any_cast<RType::Protocol::ShootData>(event.data);

    GameEngine::Entity entity = _gameEngine.registry.spawnEntity();

    struct rtype::Entity entityShoot = {.id = static_cast<uint16_t>(entity),
        .idTexture = static_cast<uint8_t> (rtype::TextureType::SHOOT),
        .positionX = static_cast<float>(shootInfo.x),
        .positionY = static_cast<float>(shootInfo.y),
        .directionX = 1000.0,
        .directionY = 0};
    _entityManager.setEntity(entityShoot, entity, _gameEngine.registry);
    std::cout << "Shoot entity number : " << entity << std::endl;
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entityShoot);
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
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
        .idTexture = static_cast<uint8_t> (rtype::TextureType::NONE),
        .positionX = transforms[moveInfo.id]->position.x,
        .positionY = transforms[moveInfo.id]->position.y,
        .directionX = transforms[moveInfo.id]->velocity.x,
        .directionY = transforms[moveInfo.id]->velocity.y};
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity, sizeof(entity));
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
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::EntityId>(entity, sizeof(entity));
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
        case static_cast<uint8_t>(rtype::PacketType::SHOOT):
            handleShoot(event);
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
        transform->position += transform->velocity * _gameEngine.deltaTime.getDeltaTime() * rtype::PLAYER_SPEED;
        std::cout << "Entity : " << i << " -> " << transform->position.x << std::endl;
        std::cout << "Entity : " << i << " -> " << transform->position.y << std::endl;
        std::cout << "Entity : " << i << " -> " << transform->velocity.x << std::endl;
        std::cout << "Entity : " << i << " -> " << transform->velocity.y << std::endl;
        struct rtype::Entity entity = {.id = static_cast<uint16_t>(i),
            .positionX = transform->position.x,
            .positionY = transform->position.y,
            .directionX = transform->velocity.x,
            .directionY = transform->velocity.y};
        std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity, sizeof(entity));
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
        _gameEngine.deltaTime.update();
        if (_eventQueue.size() != 0)
            handleEvent();
        // for (auto &transform : _gameEngine.registry.getComponent<GameEngine::TransformComponent>()) {
        //     if (!transform.has_value())
        //         continue;
        // }
        if (_deltaTime.count() > 0.1) {
            updateEntities();
            _lastTime = now;
        }
    }
}
