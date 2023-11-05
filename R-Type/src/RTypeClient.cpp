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
#include "components/MusicComponent.hpp"
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
    _points = 0;
    setGameEngine();
    setupGame();
    GameEngine::Entity scoreTitle = _gameEngine.registry.spawnEntity();
    GameEngine::TextComponent textTitle{"SCORE : ", "R-Type/fonts/Valoon.ttf", 10, GameEngine::Text(), true, 10};
    textTitle.text.load(textTitle.str, _gameEngine.assetManager.getFont("R-Type/fonts/Valoon.ttf").getFont(), textTitle.size);
    textTitle.text.setPosition(GameEngine::Vector2<float>{5, 5});
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(scoreTitle, textTitle);

    GameEngine::Entity score = _gameEngine.registry.spawnEntity();
    GameEngine::TextComponent text{std::to_string(_points), "R-Type/fonts/Valoon.ttf", 10, GameEngine::Text(), true, 10};
    text.text.load(text.str, _gameEngine.assetManager.getFont("R-Type/fonts/Valoon.ttf").getFont(), text.size);
    text.text.setPosition(GameEngine::Vector2<float>{50, 5});
    _gameEngine.registry.addComponent<GameEngine::TextComponent>(score, text);
    _scoreTextEntity = score;

    GameEngine::Entity musicHolder = _gameEngine.registry.spawnEntity();
    GameEngine::MusicComponent music{"R-Type/musics/R-Type.wav", std::make_shared<GameEngine::Music>()};
    music.music->load(music.path);
    _gameEngine.registry.addComponent<GameEngine::MusicComponent>(musicHolder, music);

    _isRunning = true;
    _gameState = RType::GameState::GAME;
    std::thread network(&RType::Client::RTypeClient::startNetwork, this, std::ref(_isRunning));
    network.detach();
    gameLoop();
}

RType::Client::RTypeClient::~RTypeClient() {}

void RType::Client::RTypeClient::startNetwork(bool &isRunning)
{
    runUdpServer();
    _isRunning = false;
}

void RType::Client::RTypeClient::handleQuit()
{
    _IOContext.stop();
    if (_id != -1) {
        struct RType::Protocol::EntityIdData entityId = {.id = this->_serverId};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::EntityIdData>(entityId, sizeof(entityId));
        _udpClient.sendDataInformation(dataToSend, static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY));
        std::cout << "Player " << _serverId << " died :( !" << std::endl;
    }
    exit(0);
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

    _gameEngine.eventManager.publish<bool &>(
        static_cast<GameEngine::EventType>(GameEngine::Event::WindowIsOpen), isOpen);
    while (_isRunning && isOpen) {
        _gameEngine.deltaTime.update();
        _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(
            static_cast<GameEngine::EventType>(GameEngine::Event::PollEvent), event);
        while (event.isEvent) {
            _gameEngine.eventManager.publish<GameEngine::SEvent &>(
                static_cast<GameEngine::EventType>(GameEngine::Event::WindowCloseEvent), event.event);
            _gameEngine.eventManager.publish<GameEngine::PollEventStruct &>(
                static_cast<GameEngine::EventType>(GameEngine::Event::PollEvent), event);
        }
        if (_gameState != RType::GameState::GAME && _endScene) {
            _win = (_gameState == RType::GameState::WIN) ? true : false;
            _gameEngine.sceneManager.loadScene("WinLose");
            _endScene = false;
        }
        if (_eventQueue.size() != 0)
            handleEvent();
        _gameEngine.registry.runSystems();
        _gameEngine.sceneManager.updateCurrentScene();
        _gameEngine.eventManager.publish<bool &>(
            static_cast<GameEngine::EventType>(GameEngine::Event::WindowIsOpen), isOpen);
    }
    if (_isRunning)
        handleQuit();
}
