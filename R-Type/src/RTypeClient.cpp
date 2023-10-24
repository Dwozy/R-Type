/*
** EPITECH PROJECT, 2023
** RTypeClient.cpp
** File description:
** RTypeClient
*/

#include "RTypeClient.hpp"
#include "systems/DrawSystem.hpp"

RType::Client::RTypeClient::RTypeClient(const std::string &address, unsigned short port)
    : _serverUdpEndpoint(asio::ip::make_address(address), port), _serverTcpEndpoint(asio::ip::make_address(address), 0),
      _udpClient(_IOContext, _serverUdpEndpoint, std::ref(_eventQueue)), _tcpClient(_IOContext, _serverTcpEndpoint),
      _signal(_IOContext, SIGINT, SIGTERM)
{
    setGameEngine();
    _isRunning = true;
    _isPlayer = true;
    std::thread network(&RType::Client::RTypeClient::startNetwork, this, std::ref(_isRunning));
    network.detach();
    gameLoop();
    struct rtype::EntityId entityId = {.id = this->_id};
    std::vector<std::byte> dataToSend =
        Serialization::serializeData<struct rtype::EntityId>(entityId, sizeof(entityId));
    _udpClient.sendDataInformation(dataToSend, static_cast<uint8_t>(rtype::PacketType::DISCONNEXION));
    std::cout << "Player " << _id << " died :( !" << std::endl;
}

RType::Client::RTypeClient::~RTypeClient() {}

void RType::Client::RTypeClient::startNetwork(bool &isRunning)
{
    runTcpServer();
    _IOContext.restart();
    runUdpServer();
    isRunning = false;
}

void RType::Client::RTypeClient::runTcpServer()
{
    _signal.async_wait(std::bind(&asio::io_context::stop, &_IOContext));
    _tcpClient.run();
    _IOContext.run();
}

void RType::Client::RTypeClient::runUdpServer()
{
    _signal.async_wait(std::bind(&asio::io_context::stop, &_IOContext));
    _udpClient.run();
    _IOContext.run();
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
        _gameEngine.eventManager.publish<bool &>(GameEngine::Event::WindowIsOpen, isOpen);
    }
}
