/*
** EPITECH PROJECT, 2023
** RTypeClient.hpp
** File description:
** RTypeClient
*/

#ifndef RTYPECLIENT_HPP_
#define RTYPECLIENT_HPP_

#include <asio.hpp>
#include <cstdint>
#include "GameEngine.hpp"
#include "Protocol.hpp"
#include "UdpClient.hpp"
#include "TcpClient.hpp"
#include "Keyboard.hpp"

namespace RType::Client
{
    class RTypeClient
    {
      public:
        RTypeClient(const std::string &address = "127.0.0.1", unsigned short port = 8080);
        ~RTypeClient();
        /// @brief Start the Network from the client in a thread
        /// @param isRunning boolean to know if the server is down
        void startNetwork(bool &isRunning);
        /// @brief Game Loop from the client
        void gameLoop();
        /// @brief Function that will handle every event from the UDP Client
        void handleEvent();

        void handleTransformComponent(struct RType::Event event);
        void handleTextureComponent(struct RType::Event event);
        void handleCollisionComponent(struct RType::Event event);

        /// @brief Function that will handle when new entity needed to be create
        /// @param event struct that will contain the information about the new entity
        void handleNewEntity(struct RType::Event event);
        /// @brief Function that will handle when entity needed to be update
        /// @param event struct that will contain the information about the entity
        void handleEntity(struct RType::Event event);
        /// @brief Function that will handle when entity needed to be delete
        /// @param event struct that will contain the information about the entity
        void handleDisconnexion(struct RType::Event event);
        /// @brief Function that delete a Entity
        /// @param entity delete the corresponding entity
        void deleteEntity(struct RType::Protocol::EntityIdData entityId);
        /// @brief Function that will handle when entity needed to be move
        /// @param event struct that will contain the information about the entity
        void handlePlayerMovement();
        /// @brief Function that delete a Entity
        /// @param entity delete the corresponding entity
        void updatePlayerMovement(const GameEngine::TransformComponent &transform);

        /// @brief Set every component to the registry of the game engine
        void setGameEngineComponent();
        /// @brief Set every system to the registry of the game engine
        void setGameEngineSystem();

        void setGameEngineCallback();

        void setGameEngine();

        void setPrefab();

        void setupTextureEntity();

        void setDeleteEntityCallback();
        void setMovementEntityCallback();
        void setControllableCallback();

        void shootEvent(const GameEngine::TransformComponent &transform);
        void handlePlayerShoot();
        void runUdpServer();
        void runTcpServer();
        void handleQuit();

        void handleTextureState(struct RType::Event event);
        void setTextureState(struct RType::Protocol::StatePlayerData transformData);
        void setTextureStateCallback();

        void setTextureInformation(struct RType::Protocol::TextureData textureData, GameEngine::Entity &entity);

        void handleControllableComponent(struct RType::Event event);
        void setControllable(struct RType::Protocol::ControllableData controllableData);

        void getTransformInformation(struct RType::Protocol::TransformData transformData);
        void setTransformCallback();

        void setCollisionInformation(struct RType::Protocol::CollisionData collisionData, GameEngine::Entity &entity);

        void getCollisionInformation(struct RType::Protocol::CollisionData collisionData);
        void setCollisionCallback();

        void getTextureInformation(struct RType::Protocol::TextureData textureData);
        void setTextureCallback();

        void setupGame();
        void setupScoreText();

        void handleScore(struct RType::Event event);
        void setScoreCallback();
        void setScore(struct RType::Protocol::ScoreData scoreData);

        void playerCollisionCallback(const std::size_t &entityId,
            SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);
        void parallaxCollision(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);

        void setInputCallback();
        void handleInput(struct GameEngine::Input::InputInfo inputData);

        void handleMoveInput(std::vector<std::byte> data, struct GameEngine::Input::InputInfo input);

      protected:
      private:
        std::size_t findEntity(const std::size_t &networkId);
        bool searchEntity(const std::size_t &networkId);

        GameEngine::GameEngine _gameEngine;
        asio::io_context _IOContext;
        asio::ip::udp::endpoint _serverUdpEndpoint;
        asio::ip::tcp::endpoint _serverTcpEndpoint;
        RType::Client::UdpClient _udpClient;
        asio::signal_set _signal;
        SafeQueue<struct RType::Event> _eventQueue;
        std::size_t _scoreTextEntity;
        bool _isRunning;
        std::size_t _points;
        uint16_t _serverId;
        std::size_t _id;
        GameEngine::Input::InputType _lastInput;
        std::map<uint8_t, std::string> _listTextureTypePrefab;
        std::map<uint8_t, std::string> _listPathTextureId;
    };
} // namespace RType::Client

#endif /* !RTYPECLIENT_HPP_ */
