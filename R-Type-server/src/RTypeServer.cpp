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

void RType::Server::RTypeServer::setTimers()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    srand(time(0));

    _timers["mob"] = now;
    _timers["gameloop"] = now;
    _timers["charged"] = now;
}

RType::Server::RTypeServer::RTypeServer(unsigned short port)
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue)),
      _tcpServer(_IOContext, port)
{
    setGameEngine();
    setupGame();
    setTimers();
    _nbPlayers = 0;
    pos = 1;
    _isRunning = true;
    _chargedAttack = true;
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

void RType::Server::RTypeServer::handlingTimers()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<float> _deltaTime =
        std::chrono::duration_cast<std::chrono::duration<float>>(now - _timers["gameloop"]);
    std::chrono::duration<float> _deltaTimeSpawn =
        std::chrono::duration_cast<std::chrono::duration<float>>(now - _timers["mob"]);
    std::chrono::duration<float> _deltaTimeChargedAttack =
        std::chrono::duration_cast<std::chrono::duration<float>>(now - _timers["charged"]);

    if (_deltaTime.count() > 0.1) {
        broadcastInformation();
        _timers["gameloop"] = now;
    }
    if (_deltaTimeSpawn.count() > 2.0) {
        spawnMob();
        _timers["mob"] = now;
    }
    if (_deltaTimeChargedAttack.count() > 5.0) {
        _chargedAttack = true;
        _timers["charged"] = now;
    }
    for (auto &playerTimer : _timerLifePoint) {
        if (playerTimer.second.first)
            continue;
        std::chrono::duration<float> _deltaTimerInvicibility =
            std::chrono::duration_cast<std::chrono::duration<float>>(now - playerTimer.second.second);
        if (_deltaTimerInvicibility.count() > 3.0) {
            playerTimer.second.second = now;
            playerTimer.second.first = true;
            struct RType::Protocol::StatePlayerData statePlayer = {
                .id = playerTimer.first, .invincibility = static_cast<uint8_t>(false)};
            std::vector<std::byte> dataToSend =
                Serialization::serializeData<struct RType::Protocol::StatePlayerData>(statePlayer, sizeof(statePlayer));
            for (auto client : _udpServer.getListClients())
                _udpServer.sendInformation(static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_STATE), dataToSend, client.second);
        }
    }
}

void RType::Server::RTypeServer::handlingEndGame()
{
    if (_nbPlayers == -1) {
        std::string message = "You lose";
        std::vector<std::byte> dataToSend(message.size());
        std::transform(message.begin(), message.end(), dataToSend.begin(), [](char c) { return std::byte(c); });
        for (auto client : _udpServer.getListClients())
            _udpServer.sendInformation(static_cast<uint8_t>(RType::PacketType::STRING), dataToSend, client.second);
        _nbPlayers = 0;
    }
}

void RType::Server::RTypeServer::gameLoop()
{
    while (_isRunning) {
        _gameEngine.deltaTime.update();
        if (_eventQueue.size() != 0)
            handleEvent();
        handlingTimers();
        handlingEndGame();
        _gameEngine.registry.runSystems();
    }
}
