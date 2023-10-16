/*
** EPITECH PROJECT, 2023
** RTypeServer.cpp
** File description:
** RTypeServer
*/

#include "RTypeServer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"

void test(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms)
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

        if (!col || !tsf || !col.value().isActive)
            continue;
        selfCol.value().collider.handleCollisionFromRect(
            selfTsf.value().position, col.value().collider, tsf.value().position);
    }
}

void RType::Server::RTypeServer::startNetwork(bool &isRunning)
{
    _signal.async_wait(std::bind(&asio::io_context::stop, &_IOContext));
    _udpServer.run();
    _IOContext.run();
    isRunning = false;
}

RType::Server::RTypeServer::RTypeServer(unsigned short port)
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_eventQueue))
{
    _isRunning = true;
    std::thread network(&RType::Server::RTypeServer::startNetwork, this, std::ref(_isRunning));
    network.detach();
    gameLoop();
}

void RType::Server::RTypeServer::handleEvent()
{
    struct rtype::Event event;

    while (_eventQueue.size() != 0) {
        event = _eventQueue.pop();
        switch (event.packetType) {
        case static_cast<uint8_t>(rtype::PacketType::CONNEXION):
            // GameEngine::Entity entity = _gameEngine.registry.spawnEntity();
            std::cout << "Connexion" << std::endl;
            break;
        case static_cast<uint8_t>(rtype::PacketType::MOVE):
            std::cout << "Move" << std::endl;
            break;
        }
    }
}

RType::Server::RTypeServer::~RTypeServer() {}

void RType::Server::RTypeServer::gameLoop()
{
    std::chrono::steady_clock::time_point _lastTime;
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    // std::chrono::duration<float> dTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTime);

    // _deltaTime = dTime.count();
    _lastTime = now;
    // auto now = _gameEngine.deltaTime.getDeltaTime();
    // auto dtime = std::chrono::duration_cast<std::chrono::duration<double>>(now - _lastTime);
    while (_isRunning) {
        // time = 0;
        // while (time < 1.0)
        // if (_gameEngine.deltaTime.getDeltaTime() > 0.0001)
        //     time += _gameEngine.deltaTime.getDeltaTime();
        // std::cout << time << std::endl;
        // if (_gameEngine.deltaTime.getDeltaTime() > 0.0001)
        // _deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTime).count();
        now = std::chrono::steady_clock::now();
        auto _deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - _lastTime);
        if (_deltaTime.count() > 0.001) {
            // std::cout << "Hello" << std::endl;
            // if (!_eventQueue.size() != 0)
                // handleEvent();
            _lastTime = now;
        }
        // _gameEngine.deltaTime.update();
        // std::cout << _gameEngine.deltaTime.getDeltaTime() << std::endl;
        // _IOContext.run_one();
    }
}
