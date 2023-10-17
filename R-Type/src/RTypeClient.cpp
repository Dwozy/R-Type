/*
** EPITECH PROJECT, 2023
** RTypeClient.cpp
** File description:
** RTypeClient
*/

#include <iostream>
#include "RTypeClient.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/NetworkIdComponent.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"
#include "systems/CollisionSystem.hpp"

void parallaxCollision(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms)
{
    auto &selfCol = collisions[entityId];
    auto &selfTsf = transforms[entityId];

    if (!selfCol || !selfTsf)
    {
        std::cout << collisions.size() << std::endl;
        if (!selfTsf)
            std::cout << "NO TSF!" << std::endl;
        if (!selfCol)
            std::cout << "NO COL!" << std::endl;
        std::cout << "OUT" << std::endl;
        return;
    }
    for (std::size_t i = 0; i < collisions.size(); i++) {
        if (i == entityId)
            continue;
        auto &col = collisions[i];
        auto &tsf = transforms[i];

        if (col)
            std::cout << "Layer " << col.value().layer << std::endl;
        if (!col || !tsf || !col.value().isActive || col.value().layer != 11)
            continue;
        if (selfCol.value().collider.isColliding(selfTsf.value().position, col.value().collider, tsf.value().position))
            selfTsf.value().position.x = 199;
    }
}

RType::Client::RTypeClient::RTypeClient(const std::string &address, unsigned short port)
    : _gameEngine(800, 800), _serverUdpEndpoint(asio::ip::make_address(address), port),
      _udpClient(_IOContext, _serverUdpEndpoint, std::ref(_eventQueue)), _signal(_IOContext, SIGINT, SIGTERM)
{
    _gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
    _gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();
    _gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
    _gameEngine.registry.registerComponent<GameEngine::CameraComponent>();
    _gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    _gameEngine.registry.registerComponent<GameEngine::TextComponent>();
    _gameEngine.registry.registerComponent<GameEngine::PressableComponent>();
    _gameEngine.registry.registerComponent<GameEngine::NetworkIdComponent>();

    GameEngine::Entity camera = _gameEngine.registry.spawnEntity();
    GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 200.0f, 200.0f)}};
    auto &refCamera = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

    _gameEngine.window.setView(refCamera.value().view);

    GameEngine::Entity parallax1 = _gameEngine.registry.spawnEntity();
    _gameEngine.registry.addComponent<GameEngine::TransformComponent>(parallax1,
        GameEngine::TransformComponent{GameEngine::Vector2<float>(0.0, 0.0), GameEngine::Vector2<float>(-50, 0.0)});
    GameEngine::Rectf collider(199, 0, 30, 200);
    GameEngine::CollisionComponent col = {.collider = collider, .layer = 10};
    col.addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, parallaxCollision);
    _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(
        parallax1, col);

    auto &parallax1Tex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(
        parallax1, GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), true, {}});
    parallax1Tex.value().texture.load("R-Type/assets/parallax.png", GameEngine::Rect<int>(0, 0, 1080, 1080));
    parallax1Tex.value().sprite.load(parallax1Tex.value().texture);
    parallax1Tex.value().sprite.setScale(0.1851, 0.1851);

    // GameEngine::Entity parallax2 = _gameEngine.registry.spawnEntity();
    // _gameEngine.registry.addComponent<GameEngine::TransformComponent>(parallax2,
    //     GameEngine::TransformComponent{GameEngine::Vector2<float>(199.0, 0.0), GameEngine::Vector2<float>(-50, 0.0)});
    // auto &col2 = _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(
    //     parallax2, GameEngine::CollisionComponent{.collider = collider, .layer = 10});
    // col2.value()
    //     .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
    //                    SparseArray<GameEngine::TransformComponent> &)>,
    //         GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, parallaxCollision);

    // auto &parallax2Tex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(
    //     parallax2, GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), true, {}});
    // parallax2Tex.value().texture.load("R-Type/assets/parallax.png", GameEngine::Rect<int>(0, 0, 1080, 1080));
    // parallax2Tex.value().sprite.load(parallax2Tex.value().texture);
    // parallax2Tex.value().sprite.setScale(0.1851, 0.1851);

    GameEngine::Entity parallaxRange = _gameEngine.registry.spawnEntity();
    _gameEngine.registry.addComponent<GameEngine::TransformComponent>(parallaxRange,
        GameEngine::TransformComponent{GameEngine::Vector2<float>(-20.0, 0), GameEngine::Vector2<float>(0.0, 0.0)});
    _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(
        parallaxRange, GameEngine::CollisionComponent{.collider = GameEngine::Rectf(0, 0, 20, 200), .layer = 11});

    auto &refHandlerNew = _gameEngine.eventManager.addHandler<struct rtype::Entity>(GameEngine::Event::GetNewEntity);
    auto handleNew = std::bind(&RType::Client::RTypeClient::entitySpawn, this, std::placeholders::_1);
    refHandlerNew.subscribe(handleNew);

    auto &refHandlerUpdate = _gameEngine.eventManager.addHandler<struct rtype::Entity>(GameEngine::Event::GetEntity);
    auto handleUpdate = std::bind(&RType::Client::RTypeClient::updateEntity, this, std::placeholders::_1);
    refHandlerUpdate.subscribe(handleUpdate);

    auto &refHandlerDelete =
        _gameEngine.eventManager.addHandler<struct rtype::EntityId>(GameEngine::Event::DeleteEntity);
    auto handleDelete = std::bind(&RType::Client::RTypeClient::deleteEntity, this, std::placeholders::_1);
    refHandlerDelete.subscribe(handleDelete);

    GameEngine::DrawSystem drawSystem(_gameEngine.window);
    GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());
    GameEngine::PressableSystem pressableSystem(_gameEngine.window);
    GameEngine::CollisionSystem collisionSystem;

    GameEngine::ControlSystem controlSystem;
    _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                       SparseArray<GameEngine::ControllableComponent> &)>,
        GameEngine::TransformComponent, GameEngine::ControllableComponent>(controlSystem);

    _gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);

    _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> & collisions)>,
        GameEngine::CollisionComponent>(collisionSystem);

    _gameEngine.registry.addSystem<GameEngine::PressableFunction, GameEngine::TransformComponent,
        GameEngine::TextureComponent, GameEngine::PressableComponent>(pressableSystem);

    _gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TextComponent> &, SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TextComponent, GameEngine::TextureComponent>(drawSystem);

    _isRunning = true;
    _isPlayer = true;
    std::thread network(&RType::Client::RTypeClient::startNetwork, this, std::ref(_isRunning));
    network.detach();
    gameLoop();
}

RType::Client::RTypeClient::~RTypeClient() {}

void RType::Client::RTypeClient::handleQuitClient()
{
    struct rtype::EntityId entityId = {.id = this->_id};
    std::vector<std::byte> dataToSend = Serialization::serializeData<struct rtype::EntityId>(entityId);
    this->_udpClient.sendDataInformation(dataToSend, static_cast<uint8_t>(rtype::PacketType::DISCONNEXION));
    this->_IOContext.stop();
}

void RType::Client::RTypeClient::startNetwork(bool &isRunning)
{
    _signal.async_wait(std::bind(&RType::Client::RTypeClient::handleQuitClient, this));
    _udpClient.run();
    _IOContext.run();
    isRunning = false;
}

void RType::Client::RTypeClient::entitySpawn(const struct rtype::Entity entity)
{
    GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity();

    _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
        newEntity, GameEngine::NetworkIdComponent{entity.id});
    _entityManager.setPlayerEntity(entity.positionX, entity.positionY, newEntity, _gameEngine.registry);
    if (_isPlayer) {
        _entityManager.setControlPlayerEntity(newEntity, _gameEngine.registry);
        _isPlayer = false;
        _id = entity.id;
    }
}

void RType::Client::RTypeClient::deleteEntity(const struct rtype::EntityId entityId)
{
    std::size_t id = _findEntity(entityId.id);
    GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
    _gameEngine.registry.killEntity(entity);
}

void RType::Client::RTypeClient::updateEntity(const struct rtype::Entity entity)
{
    auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

    if (!_searchEntity(entity.id)) {
        GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity();
        _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
            newEntity, GameEngine::NetworkIdComponent{entity.id});
        _entityManager.setPlayerEntity(entity.positionX, entity.positionY, newEntity, _gameEngine.registry);
        return;
    }

    std::size_t id = _findEntity(entity.id);

    if (entity.id > transforms.size())
        throw;
    if (!transforms[id].has_value()) {
        GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity();
        _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
            newEntity, GameEngine::NetworkIdComponent{entity.id});
        _entityManager.setPlayerEntity(entity.positionX, entity.positionY, newEntity, _gameEngine.registry);
    } else {
        transforms[id]->velocity.x = entity.directionX;
        transforms[id]->velocity.y = entity.directionY;
        transforms[id]->position.x = entity.positionX;
        transforms[id]->position.y = entity.positionY;
    }
}

void RType::Client::RTypeClient::handleNewEntity(struct rtype::Event event)
{
    struct rtype::Entity entity = std::any_cast<struct rtype::Entity>(event.data);
    _gameEngine.eventManager.getHandler<struct rtype::Entity>(GameEngine::Event::GetNewEntity).publish(entity);
}

void RType::Client::RTypeClient::handleEntity(struct rtype::Event event)
{
    struct rtype::Entity entity = std::any_cast<struct rtype::Entity>(event.data);
    _gameEngine.eventManager.getHandler<struct rtype::Entity>(GameEngine::Event::GetEntity).publish(entity);
}

void RType::Client::RTypeClient::handleDisconnexion(struct rtype::Event event)
{
    struct rtype::EntityId entity = std::any_cast<struct rtype::EntityId>(event.data);
    _gameEngine.eventManager.getHandler<struct rtype::EntityId>(GameEngine::Event::DeleteEntity).publish(entity);
}

void RType::Client::RTypeClient::handleEvent()
{
    struct rtype::Event event;

    while (_eventQueue.size() != 0) {
        event = _eventQueue.pop();
        switch (event.packetType) {
        case static_cast<uint8_t>(rtype::PacketType::ENTITY):
            handleEntity(event);
            break;
        case static_cast<uint8_t>(rtype::PacketType::CONNECTED):
            handleNewEntity(event);
            break;
        case static_cast<uint8_t>(rtype::PacketType::DISCONNEXION):
            handleDisconnexion(event);
            break;
        }
    }
}

void RType::Client::RTypeClient::gameLoop()
{
    while (_isRunning && _gameEngine.window.isOpen()) {
        _gameEngine.deltaTime.update();
        GameEngine::SEvent event;
        while (_gameEngine.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _gameEngine.window.close();
        }
        if (_eventQueue.size() != 0)
            handleEvent();
        _gameEngine.registry.runSystems();
    }
}

std::size_t RType::Client::RTypeClient::_findEntity(const std::size_t &networkId)
{
    const auto &ids = _gameEngine.registry.getComponent<GameEngine::NetworkIdComponent>();

    for (std::size_t i = 0; i < ids.size(); i++) {
        const auto &id = ids[i];

        if (id && id.value().id == networkId)
            return i;
    }
    throw; // Entity not found
}

bool RType::Client::RTypeClient::_searchEntity(const std::size_t &networkId)
{
    const auto &ids = _gameEngine.registry.getComponent<GameEngine::NetworkIdComponent>();

    for (std::size_t i = 0; i < ids.size(); i++) {
        const auto &id = ids[i];

        if (id && id.value().id == networkId)
            return true;
    }
    return false;
}
