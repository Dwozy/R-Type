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
#include "components/GravityComponent.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "utils/Vector.hpp"

RType::Client::RTypeClient::RTypeClient(const std::string &address, unsigned short port)
    : _serverUdpEndpoint(asio::ip::make_address(address), port), _serverTcpEndpoint(asio::ip::make_address(address), 0),
      _udpClient(_IOContext, _serverUdpEndpoint, std::ref(_eventQueue)), /*_tcpClient(_IOContext, _serverTcpEndpoint),*/
      _signal(_IOContext, SIGINT, SIGTERM)
{
    _id = 0;
    setGameEngine();
    _gameEngine.assetManager.loadTexture("R-Type/assets/image.png", {0, 0, 32, 16});
    _gameEngine.assetManager.loadTexture("R-Type/assets/r-typesheet1.gif", {251, 107, 12, 4});
    _gameEngine.assetManager.loadTexture("R-Type/assets/parallax.png", {0, 0, 1080, 1080});
    _gameEngine.assetManager.loadTexture("R-Type/assets/pata_pata.gif", {7, 8, 17, 20});

    _gameEngine.prefabManager.loadPrefabFromFile("config/NonPlayerStarship.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/Player.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/ParallaxCollision.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/Parallax.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/Shoot.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/PataPata.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapUp.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapDown.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapLeft.json");
    _gameEngine.prefabManager.loadPrefabFromFile("config/BorderMapRight.json");

    _listTextureTypePrefab.insert({static_cast<uint8_t>(rtype::TextureType::PLAYER), "player"});
    _listTextureTypePrefab.insert({static_cast<uint8_t>(rtype::TextureType::SHOOT), "shoot"});
    _listTextureTypePrefab.insert({static_cast<uint8_t>(rtype::TextureType::MOB), "patapata"});

    _isAlive = true;
    _isRunning = true;
    _isPlayer = true;
    std::thread network(&RType::Client::RTypeClient::startNetwork, this, std::ref(_isRunning));
    network.detach();
    gameLoop();
}

RType::Client::RTypeClient::~RTypeClient() {}

void RType::Client::RTypeClient::startNetwork(bool &isRunning)
{
    // runTcpServer();
    // _IOContext.restart();
    runUdpServer();
    _isRunning = false;
}

void RType::Client::RTypeClient::runTcpServer()
{
    // _signal.async_wait(std::bind(&asio::io_context::stop, &_IOContext));
    // _tcpClient.run();
    // _IOContext.run();
}

void RType::Client::RTypeClient::handleQuit()
{
    _IOContext.stop();
    struct rtype::EntityId entityId = {.id = this->_serverId};
    std::vector<std::byte> dataToSend =
        Serialization::serializeData<struct rtype::EntityId>(entityId, sizeof(entityId));
    _udpClient.sendDataInformation(dataToSend, static_cast<uint8_t>(rtype::PacketType::DESTROY));
    std::cout << "Player " << _serverId << " died :( !" << std::endl;
}

void RType::Client::RTypeClient::runUdpServer()
{
    auto handleQuitCallback = std::bind(&RType::Client::RTypeClient::handleQuit, this);
    _signal.async_wait(handleQuitCallback);
    _udpClient.run();
    _IOContext.run();
    _isRunning = false;
}

void RType::Client::RTypeClient::gameLoop()
{
    bool isOpen = false;
    GameEngine::PollEventStruct event;

    _gameEngine.eventManager.publish<bool &>(GameEngine::Event::WindowIsOpen, isOpen);
    while (_isRunning && isOpen) {
        _gameEngine.deltaTime.update();
        _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(GameEngine::Event::PollEvent, event);
        while (event.isEvent) {
            _gameEngine.eventManager.publish<GameEngine::SEvent &>(GameEngine::Event::WindowCloseEvent, event.event);
            _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(GameEngine::Event::PollEvent, event);
        }
        if (_eventQueue.size() != 0)
            handleEvent();
        _gameEngine.registry.runSystems();
        handlePlayerMovement();
        handlePlayerShoot();
        _gameEngine.eventManager.publish<bool &>(GameEngine::Event::WindowIsOpen, isOpen);
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
