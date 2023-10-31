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
    setGameEngine();
    setupGame();
    _nbPlayers = 0;
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
            std::string message = "You lose";
            std::cout << "LOSE" << std::endl;
            std::vector<std::byte> dataToSend(message.size());
            std::transform(message.begin(), message.end(), dataToSend.begin(), [](char c) { return std::byte(c); });
            for (auto client : _udpServer.getListClients())
                _udpServer.sendInformation(
                    static_cast<uint8_t>(rtype::PacketType::STRING), dataToSend, client.second);
            _nbPlayers = 0;
        }
        _gameEngine.registry.runSystems();
    }
}
