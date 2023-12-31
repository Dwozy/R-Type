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
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue))
{
    setGameEngine();
    setupGame();
    setTimers();
    _killEnemy = false;
    _points = 0;
    _isRunning = true;
    _chargedAttack = true;
    _nbPlayers = 0;
    std::thread network(&RType::Server::RTypeServer::startNetwork, this, std::ref(_isRunning));
    gameLoop();
    network.join();
}

RType::Server::RTypeServer::~RTypeServer() {}

void RType::Server::RTypeServer::startNetwork(bool &isRunning)
{
    _signal.async_wait(std::bind(&asio::io_context::stop, &_IOContext));
    _udpServer.run();
    _IOContext.run();
    isRunning = false;
}

void RType::Server::RTypeServer::handlingEndGame()
{
    if (_nbPlayers == -1) {
        struct RType::Protocol::EndGameData endGameData = {
            .endGameState = static_cast<uint8_t>(RType::GameState::LOSE)};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::EndGameData>(endGameData, sizeof(endGameData));
        for (auto client : _udpServer.getListClients())
            _udpServer.sendInformation(
                static_cast<uint8_t>(RType::Protocol::PacketType::ENDGAME), dataToSend, client.second);
        _nbPlayers = 0;
        // _isRunning = false;
    }
    if (_points >= 150){
        struct RType::Protocol::EndGameData endGameData = {
            .endGameState = static_cast<uint8_t>(RType::GameState::WIN)};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::EndGameData>(endGameData, sizeof(endGameData));
        for (auto client : _udpServer.getListClients())
            _udpServer.sendInformation(
                static_cast<uint8_t>(RType::Protocol::PacketType::ENDGAME), dataToSend, client.second);
        // _isRunning = false;
    }
}

void RType::Server::RTypeServer::gameLoop()
{
    while (_isRunning) {
        _gameEngine.deltaTime.update();
        _gameEngine.registry.runSystems();
        if (_eventQueue.size() != 0)
            handleEvent();
        handlingTimers();
        handlingEndGame();
    }
    _IOContext.stop();
}
