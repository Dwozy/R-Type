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

    auto rightBoxEntity =
        _gameEngine.prefabManager.createEntityFromPrefab("destroy_right_box", _gameEngine.registry, false);
    auto &rightBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[rightBoxEntity];
    rightBox.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyCallback);
    _listIdType.insert({static_cast<uint16_t>(rightBoxEntity), static_cast<uint8_t>(rtype::EntityType::NONE)});

    auto leftBoxEntity =
        _gameEngine.prefabManager.createEntityFromPrefab("destroy_left_box", _gameEngine.registry, false);
    auto &leftBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[leftBoxEntity];
    leftBox.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyCallback);
    _listIdType.insert({static_cast<uint16_t>(leftBoxEntity), static_cast<uint8_t>(rtype::EntityType::NONE)});

    auto borderBoxUp = _gameEngine.prefabManager.createEntityFromPrefab("border_map_up", _gameEngine.registry, false);
    _listIdType.insert({static_cast<uint16_t>(borderBoxUp), static_cast<uint8_t>(rtype::EntityType::NONE)});

    auto borderBoxDown =
        _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry, false);
    _listIdType.insert({static_cast<uint16_t>(borderBoxDown), static_cast<uint8_t>(rtype::EntityType::NONE)});

    auto borderBoxLeft =
        _gameEngine.prefabManager.createEntityFromPrefab("border_map_left", _gameEngine.registry, false);
    _listIdType.insert({static_cast<uint16_t>(borderBoxLeft), static_cast<uint8_t>(rtype::EntityType::NONE)});

    auto borderBoxRight =
        _gameEngine.prefabManager.createEntityFromPrefab("border_map_right", _gameEngine.registry, false);
    _listIdType.insert({static_cast<uint16_t>(borderBoxRight), static_cast<uint8_t>(rtype::EntityType::NONE)});

    _nbPlayers = 0;
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

componentList RType::Server::RTypeServer::setEntitiesComponent()
{
    componentList infos;

    auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
    auto textures = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();

    for (std::size_t i = 0; i < transforms.size(); i++) {
        std::map<RType::Protocol::ComponentType, std::vector<bool>> componentInfo;
        componentInfo.insert({RType::Protocol::ComponentType::TRANSFORM, {true}});
        componentInfo.insert({RType::Protocol::ComponentType::COLLISION, {true}});
        auto texture = textures[i];
        auto transform = transforms[i];
        if (!texture && !transform)
            continue;
        if (texture) {
            std::vector<bool> distribTexture(texture->textureRects.size(), true);
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, distribTexture});
        } else
            componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, {false}});
        GameEngine::Entity entity = _gameEngine.registry.getEntityById(i);
        infos.insert({entity, componentInfo});
    }
    return infos;
}

void RType::Server::RTypeServer::broadcastEntityInformation(const GameEngine::Entity &entity)
{
    auto transform = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[entity];
    auto collision = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[entity];
    auto texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entity];

    if (!transform)
        return;
    for (auto client : _udpServer.getListClients()) {
        if (_listInfosComponent.find(client.first) == _listInfosComponent.end())
            continue;
        if (_listInfosComponent[client.first].find(entity) == _listInfosComponent[client.first].end())
            continue;
        sendTransformComponent(static_cast<uint16_t>(entity), transform->position, transform->velocity, client.second);
        if (_listInfosComponent[client.first].at(entity).at(RType::Protocol::ComponentType::COLLISION).front())
            sendCollisionComponent(static_cast<uint16_t>(entity), collision->collider, collision->layer, client.second);
        std::size_t size = _listInfosComponent[client.first][entity][RType::Protocol::ComponentType::TEXTURE].size();
        checkSendingTexture(_listInfosComponent[client.first][entity][RType::Protocol::ComponentType::TEXTURE],
            entity, client.second);
    }
}

void RType::Server::RTypeServer::broadcastInformation()
{
    broadcastTransformComponent();
    broadcastTextureComponent();
    broadcastCollisionComponent();
}

void RType::Server::RTypeServer::handleShoot(struct rtype::Event event)
{
    auto shootInfo = std::any_cast<RType::Protocol::ShootData>(event.data);
    GameEngine::Entity shootEntity =
        _gameEngine.prefabManager.createEntityFromPrefab("shoot", _gameEngine.registry, false);
    GameEngine::Recti rectPlayer = {0, 0, 0, 0};

    auto &shootPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[shootEntity];
    for (auto &entityTexture : _listIdType) {
        if (entityTexture.second == static_cast<uint8_t>(rtype::EntityType::PLAYER)) {
            rectPlayer = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entityTexture.first]
                             .value()
                             .textureRects[0];
            break;
        }
    }
    auto &shootCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[shootEntity];
    auto destroyShootCallback = std::bind(&RType::Server::RTypeServer::destroyEntityCallback, this,
        std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    shootCollider.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyShootCallback);
    shootPos->position =
        GameEngine::Vector2<float>(shootInfo.x + (rectPlayer.width / 2), shootInfo.y + (rectPlayer.height / 2));
    struct rtype::Entity entityShoot = {.id = static_cast<uint16_t>(shootEntity),
        .idTexture = static_cast<uint8_t>(rtype::EntityType::SHOOT),
        .positionX = shootPos->position.x,
        .positionY = shootPos->position.y,
        .directionX = shootPos->velocity.x,
        .directionY = shootPos->velocity.y};
    _listIdType.insert({static_cast<uint16_t>(shootEntity), static_cast<uint8_t>(rtype::EntityType::SHOOT)});
    std::vector<std::byte> dataToSend =
        Serialization::serializeData<struct rtype::Entity>(entityShoot, sizeof(entityShoot));
    // _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
}

void RType::Server::RTypeServer::handleMove(struct rtype::Event event)
{
    auto moveInfo = std::any_cast<RType::Protocol::MoveData>(event.data);

    auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

    if (moveInfo.id > transforms.size())
        return;
    if (!transforms[moveInfo.id])
        return;
    // transforms[moveInfo.id]->position = {moveInfo.x, moveInfo.y};
    transforms[moveInfo.id]->velocity.x = moveInfo.dx;
    transforms[moveInfo.id]->velocity.y = moveInfo.dy;
    broadcastInformation();
    // struct rtype::Entity entity = {.id = static_cast<uint16_t>(moveInfo.id),
    //     .idTexture = _listIdType.at(moveInfo.id),
    //     .positionX = transforms[moveInfo.id]->position.x,
    //     .positionY = transforms[moveInfo.id]->position.y,
    //     .directionX = transforms[moveInfo.id]->velocity.x,
    //     .directionY = transforms[moveInfo.id]->velocity.y};
    // std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::Entity>(entity, sizeof(entity));
    // _udpServer.broadcastInformation(sta  tic_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
}

void RType::Server::RTypeServer::handleDestroy(struct rtype::Event event)
{
    struct RType::Protocol::EntityIdData entity = std::any_cast<struct RType::Protocol::EntityIdData>(event.data);

    try {
        GameEngine::Entity getEntity = _gameEngine.registry.getEntityById(entity.id);
        if (_listIdType[entity.id] == static_cast<uint8_t>(rtype::EntityType::PLAYER))
            pos--;
        _gameEngine.registry.killEntity(getEntity);
        _listLifePoints.erase(static_cast<uint16_t>(entity.id));
        _listIdType.erase(static_cast<uint16_t>(entity.id));
        struct RType::Protocol::EntityIdData entityId = {.id = entity.id};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::EntityIdData>(entityId, sizeof(entityId));
        for (auto client : _udpServer.getListClients()) {
            _listInfosComponent[event.port].erase(static_cast<uint16_t>(entity.id));
            _udpServer.sendInformation(static_cast<uint8_t>(rtype::PacketType::DESTROY), dataToSend, client.second);
        }
    } catch (const std::exception &e) {
        return;
    }
}

void RType::Server::RTypeServer::handleEvent()
{
    struct rtype::Event event;

    while (_eventQueue.size() != 0) {
        event = _eventQueue.pop();
        switch (event.packetType) {
        case static_cast<uint8_t>(rtype::PacketType::CONNEXION):
            handleConnexion(event);
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
        case static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_RES):
            handleTextureResponse(event);
            break;
        case static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION_RES):
            handleCollisionResponse(event);
            break;
        }
    }
}

void RType::Server::RTypeServer::spawnMob()
{
    GameEngine::Entity mobEntity =
        _gameEngine.prefabManager.createEntityFromPrefab("patapata", _gameEngine.registry, false);
    auto &entityPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[mobEntity];
    float randPosY = (rand() % 180) + 10;
    entityPos->position = GameEngine::Vector2<float>(200, randPosY);
    auto &entityCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[mobEntity];
    auto destroyMobCallback = std::bind(&RType::Server::RTypeServer::destroyEntityCallback, this, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3);
    entityCollider.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyMobCallback);

    struct rtype::Entity newEntity = {.id = static_cast<uint16_t>(mobEntity),
        .idTexture = static_cast<uint8_t>(rtype::EntityType::MOB),
        .positionX = entityPos->position.x,
        .positionY = entityPos->position.y,
        .directionX = entityPos->velocity.x,
        .directionY = entityPos->velocity.y};
    _listIdType.insert({static_cast<uint16_t>(mobEntity), static_cast<uint8_t>(rtype::EntityType::MOB)});

    std::map<RType::Protocol::ComponentType, std::vector<bool>> componentInfo;
    componentInfo.insert({RType::Protocol::ComponentType::TRANSFORM, {true}});
    componentInfo.insert({RType::Protocol::ComponentType::COLLISION, {true}});
    auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[mobEntity];
    if (texture) {
        std::vector<bool> distribTexture(texture->textureRects.size(), true);
        componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, distribTexture});
    } else
        componentInfo.insert({RType::Protocol::ComponentType::TEXTURE, {false}});

    for (auto &listInfo : _listInfosComponent)
        listInfo.second.insert({mobEntity, componentInfo});
    broadcastInformation();
    // _udpServer.sendInformation(static_cast<uint8_t>(rtype::PacketType::ENTITY), dataToSend);
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
            broadcastInformation();
            _lastTime = now;
        }
        if (_deltaTimeSpawn.count() > 2.0) {
            spawnMob();
            _lastTimeSpawn = now;
        }
        if (_nbPlayers == -1) {
            // std::string message = "You lose";
            // std::vector<std::byte> data(message.size());
            // std::transform(message.begin(), message.end(), data.begin(), [](char c) { return std::byte(c); });
            // _udpServer.broadcastInformation(static_cast<uint8_t>(rtype::PacketType::STRING), data);
            // _nbPlayers = 0;
        }
        _gameEngine.registry.runSystems();
    }
}
