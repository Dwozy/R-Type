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
#include "systems/PositionSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "utils/Rect.hpp"
#include "RType.hpp"

void RType::Server::RTypeServer::destroyEntityCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms)
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

        if (!col || !tsf || !col.value().isActive || (col.value().layer != 20 && col.value().layer != 19))
            continue;
        if (selfCol.value().collider.isColliding(
                selfTsf.value().position, col.value().collider, tsf.value().position)) {
            struct rtype::EntityId entityId = {.id = static_cast<uint16_t>(i)};
            struct rtype::Event destroyEvent = {
                .packetType = static_cast<uint8_t>(rtype::PacketType::DESTROY), .data = entityId};
            _eventQueue.push(destroyEvent);
        }
    }
}

void RType::Server::RTypeServer::replaceEntityCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms)
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

        if (!col || !tsf || !col.value().isActive || (col.value().layer != 25))
            continue;
        selfCol.value().collider.handleCollisionFromRect(
            selfTsf.value().position, col.value().collider, tsf.value().position);
        selfTsf.value().velocity = {0, 0};
    }
}

RType::Server::RTypeServer::RTypeServer(unsigned short port)
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue)),
      _tcpServer(_IOContext, port)
{
    _gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
    _gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();
    _gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    _gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();

    _gameEngine.prefabManager.loadPrefabFromFile("config/NonPlayerStarship.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/Player.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/ParallaxCollision.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/Parallax.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/PataPata.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/Shoot.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/DestroyEntityLeft.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/DestroyEntityRight.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapUp.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapDown.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapLeft.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapRight.json");

    GameEngine::CollisionSystem collisionSystem;
    _gameEngine.registry
        .addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> &)>, GameEngine::CollisionComponent>(
            collisionSystem);

    auto destroyCallback = std::bind(&RType::Server::RTypeServer::destroyEntityCallback, this, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3);

    auto rightBoxEntity = _gameEngine.prefabManager.createEntityFromPrefab("destroy_right_box", _gameEngine.registry);
    auto &rightBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[rightBoxEntity];
    rightBox.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyCallback);
    _listIdTexture.insert({static_cast<uint16_t>(rightBoxEntity), static_cast<uint8_t>(rtype::TextureType::NONE)});

    auto leftBoxEntity = _gameEngine.prefabManager.createEntityFromPrefab("destroy_left_box", _gameEngine.registry);
    auto &leftBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[leftBoxEntity];
    leftBox.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyCallback);
    _listIdTexture.insert({static_cast<uint16_t>(leftBoxEntity), static_cast<uint8_t>(rtype::TextureType::NONE)});

    auto borderBoxUp = _gameEngine.prefabManager.createEntityFromPrefab("border_map_up", _gameEngine.registry);
    _listIdTexture.insert({static_cast<uint16_t>(borderBoxUp), static_cast<uint8_t>(rtype::TextureType::NONE)});

    auto borderBoxDown = _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry);
    _listIdTexture.insert({static_cast<uint16_t>(borderBoxDown), static_cast<uint8_t>(rtype::TextureType::NONE)});

    auto borderBoxLeft = _gameEngine.prefabManager.createEntityFromPrefab("border_map_left", _gameEngine.registry);
    _listIdTexture.insert({static_cast<uint16_t>(borderBoxLeft), static_cast<uint8_t>(rtype::TextureType::NONE)});

    auto borderBoxRight = _gameEngine.prefabManager.createEntityFromPrefab("border_map_right", _gameEngine.registry);
    _listIdTexture.insert({static_cast<uint16_t>(borderBoxRight), static_cast<uint8_t>(rtype::TextureType::NONE)});

    pos = 1;
    GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());
    _gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);

    _isRunning = true;
    std::thread network(&RType::Server::RTypeServer::startNetwork, this, std::ref(_isRunning));
    network.detach();
    gameLoop();
}

RType::Server::RTypeServer::~RTypeServer() {}

void RType::Server::RTypeServer::startNetwork(bool &isRunning)
{
    _signal.async_wait(std::bind(&asio::io_context::stop, &_IOContext));
    // _tcpServer.run();
    _udpServer.run();
    _IOContext.run();
    isRunning = false;
}

void RType::Server::RTypeServer::handleConnexion()
{
    GameEngine::Entity entity = _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry);
    auto &entityPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[entity];
    entityPos.value().position = GameEngine::Vector2<float>(pos * 25, pos * 25);

    auto &entityCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[entity];

    auto colliderCallback = std::bind(&RType::Server::RTypeServer::replaceEntityCallback, this, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3);
    entityCollider.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, colliderCallback);

    struct rtype::Entity newEntity = {.id = static_cast<uint16_t>(entity),
        .idTexture = static_cast<uint8_t>(rtype::TextureType::PLAYER),
        .positionX = entityPos.value().position.x,
        .positionY = entityPos.value().position.y,
        .directionX = entityPos.value().velocity.x,
        .directionY = entityPos.value().velocity.y};
    pos++;
    _listIdTexture.insert({static_cast<uint16_t>(entity), static_cast<uint8_t>(rtype::TextureType::PLAYER)});
    std::cout << "Player " << entity << " spawned !" << std::endl;
    std::vector<std::byte> dataToSend =
        Serialization::serializeData<struct rtype::Entity>(newEntity, sizeof(newEntity));
    std::cout << "Has to send " << dataToSend.size() << std::endl;
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::CONNECTED), dataToSend);
}

void RType::Server::RTypeServer::handleShoot(struct rtype::Event event)
{
    auto shootInfo = std::any_cast<RType::Protocol::ShootData>(event.data);
    GameEngine::Entity shootEntity = _gameEngine.prefabManager.createEntityFromPrefab("shoot", _gameEngine.registry);
    GameEngine::Recti rectPlayer = {0, 0, 0, 0};

    auto &shootPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[shootEntity];
    for (auto &entityTexture : _listIdTexture) {
        if (entityTexture.second == static_cast<uint8_t>(rtype::TextureType::PLAYER)) {
            rectPlayer = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entityTexture.first]
                             .value()
                             .textureRects[0];
            break;
        }
    }
    shootPos.value().position =
        GameEngine::Vector2<float>(shootInfo.x + (rectPlayer.width / 2), shootInfo.y + (rectPlayer.height / 2));

    struct rtype::Entity entityShoot = {.id = static_cast<uint16_t>(shootEntity),
        .idTexture = static_cast<uint8_t>(rtype::TextureType::SHOOT),
        .positionX = shootPos.value().position.x,
        .positionY = shootPos.value().position.y,
        .directionX = shootPos.value().velocity.x,
        .directionY = shootPos.value().velocity.y};
    _listIdTexture.insert({static_cast<uint16_t>(shootEntity), static_cast<uint8_t>(rtype::TextureType::SHOOT)});
    std::vector<std::byte> dataToSend =
        Serialization::serializeData<struct rtype::Entity>(entityShoot, sizeof(entityShoot));
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
        .idTexture = _listIdTexture.at(moveInfo.id),
        .positionX = transforms[moveInfo.id]->position.x,
        .positionY = transforms[moveInfo.id]->position.y,
        .directionX = transforms[moveInfo.id]->velocity.x,
        .directionY = transforms[moveInfo.id]->velocity.y};
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity, sizeof(entity));
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
}

void RType::Server::RTypeServer::handleDestroy(struct rtype::Event event)
{
    struct rtype::EntityId entity = std::any_cast<struct rtype::EntityId>(event.data);
    auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

    if (entity.id > transforms.size())
        return;
    GameEngine::Entity getEntity = _gameEngine.registry.getEntityById(entity.id);
    if (_listIdTexture[entity.id] == static_cast<uint8_t>(rtype::TextureType::PLAYER))
        pos--;
    _gameEngine.registry.killEntity(getEntity);
    _listIdTexture.erase(static_cast<uint16_t>(entity.id));
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::EntityId>(entity, sizeof(entity));
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::DESTROY), dataToSend);
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
        case static_cast<uint8_t>(rtype::PacketType::DESTROY):
            handleDestroy(event);
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
        struct rtype::Entity entity = {.id = static_cast<uint16_t>(i),
            .idTexture = _listIdTexture.at(static_cast<uint16_t>(i)),
            .positionX = transform->position.x,
            .positionY = transform->position.y,
            .directionX = transform->velocity.x,
            .directionY = transform->velocity.y};
        std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity, sizeof(entity));
        _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
    }
}

void RType::Server::RTypeServer::spawnMob()
{
    GameEngine::Entity mobEntity = _gameEngine.prefabManager.createEntityFromPrefab("patapata", _gameEngine.registry);
    auto &entityPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[mobEntity];
    float randPosY = (rand() % 180) + 10;
    entityPos.value().position = GameEngine::Vector2<float>(200, randPosY);

    struct rtype::Entity newEntity = {.id = static_cast<uint16_t>(mobEntity),
        .idTexture = static_cast<uint8_t>(rtype::TextureType::MOB),
        .positionX = entityPos.value().position.x,
        .positionY = entityPos.value().position.y,
        .directionX = entityPos.value().velocity.x,
        .directionY = entityPos.value().velocity.y};
    pos++;
    _listIdTexture.insert({static_cast<uint16_t>(mobEntity), static_cast<uint8_t>(rtype::TextureType::MOB)});
    std::vector<std::byte> dataToSend =
        Serialization::serializeData<struct rtype::Entity>(newEntity, sizeof(newEntity));
    _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
}

void RType::Server::RTypeServer::gameLoop()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point _lastTime = now;
    std::chrono::steady_clock::time_point _lastTimeSpawn = now;
    srand(time(0));

    while (_isRunning) {
        now = std::chrono::steady_clock::now();
        auto _deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTime);
        auto _deltaTimeSpawn = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTimeSpawn);
        _gameEngine.deltaTime.update();
        if (_eventQueue.size() != 0)
            handleEvent();
        if (_deltaTime.count() > 0.1) {
            updateEntities();
            _lastTime = now;
        }
        if (_deltaTimeSpawn.count() > 2.0) {
            spawnMob();
            _lastTimeSpawn = now;
        }
        _gameEngine.registry.runSystems();
    }
}
