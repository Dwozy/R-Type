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
        /// @brief Function that will handle when a End game information is received
        /// @param event struct that will contain the information abour the endgame
        void handleEndGame(struct RType::Event event);
        /// @brief Function that will handle when a Transform component is received
        /// @param event struct that will contain the information abour the Transform component
        void handleTransformComponent(struct RType::Event event);
        /// @brief Function that will handle when a Texture component is received
        /// @param event struct that will contain the information abour the Texture component
        void handleTextureComponent(struct RType::Event event);
        /// @brief Function that will handle when a Collision component is received
        /// @param event struct that will contain the information abour the Collision component
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
        /// @brief Set every callback of the eventManager in the game engine
        void setGameEngineCallback();
        /// @brief Set information of the game engine
        void setGameEngine();
        /// @brief Set Game Engine scene
        void setGameEngineScene();
        /// @brief Function that will be called when the callback is triggered for the endgame
        /// @param endGameData struct that will contain the information about the end game
        void setEndGameState(struct RType::Protocol::EndGameData endGameData);
        /// @brief Set EndGame callback
        void setEndGameCallback();
        /// @brief Set Delete entity callback
        void setDeleteEntityCallback();
        /// @brief Function that will handle when entity needed to be move
        /// @param event struct that will contain the information about the entity
        void handlePlayerMovement();
        /// @brief Function that delete a Entity
        /// @param entity delete the corresponding entity
        void updatePlayerMovement(const GameEngine::TransformComponent &transform);
        /// @brief Set all the needed prefab for the client
        void setPrefab();
        /// @brief Set all the need textures for entities
        void setupTextureEntity();
        /// @brief Set the controllable component callback
        void setControllableCallback();
        /// @brief Function that will run the udp server in a thread;
        void runUdpServer();
        /// @brief Function that will handle correctly when a client quits
        void handleQuit();
        /// @brief Function that will handle when a Texture need to be update
        /// @param event Struct that will contain the information (state) of the texture component
        void handleTextureState(struct RType::Event event);
        /// @brief Function that will update the state of a texture
        /// @param transformData Struct that will contain the state of the texture
        void setTextureState(struct RType::Protocol::StatePlayerData textureData);
        /// @brief Set the Texture State Callback
        void setTextureStateCallback();
        /// @brief Set the texture information component to a specific entity
        /// @param textureData Struct that contain the information of the texture
        /// @param entity Entity that will get the information about the texture
        void setTextureInformation(struct RType::Protocol::TextureData textureData, GameEngine::Entity &entity);
        /// @brief Function that will handle when a Controllable component is received
        /// @param event Struct that will contain the information about the controllable component
        void handleControllableComponent(struct RType::Event event);
        /// @brief Function that will set the controllable input for the client
        /// @param controllableData Struct that will contain the information and set the input information
        void setControllable(struct RType::Protocol::ControllableData controllableData);
        /// @brief Function that will handle and update the transform component of a entity
        /// @param transformData Struct that will contain de transform component information
        void getTransformInformation(struct RType::Protocol::TransformData transformData);
        /// @brief Set the transform update callback
        void setTransformCallback();
        /// @brief Function that will set the value of a collision component to a specific entity
        /// @param collisionData Struct that will contain the information about the collision
        /// @param entity Entity that will get the information about the collision
        void setCollisionInformation(struct RType::Protocol::CollisionData collisionData, GameEngine::Entity &entity);
        /// @brief Function that will handle and update the collision component information
        /// @param collisionData Struct that will contain the collision information
        void getCollisionInformation(struct RType::Protocol::CollisionData collisionData);
        /// @brief Set the collision update information callback
        void setCollisionCallback();
        /// @brief Function that will handle and upate the texture component information
        /// @param textureData Struct that will contain the texture information
        void getTextureInformation(struct RType::Protocol::TextureData textureData);
        /// @brief Set the texture update component callback
        void setTextureCallback();
        /// @brief Function that will setup every entity needed by the server
        void setupGame();
        /// @brief Function that will set the score text for the client
        void setupScoreText();
        /// @brief Function that will handle the score
        /// @param event Struct that contain the information about the score
        void handleScore(struct RType::Event event);
        /// @brief Function that set the score callback
        void setScoreCallback();
        /// @brief Function that will be triggered when the callback start, setting the score of the game
        void setScore(struct RType::Protocol::ScoreData scoreData);
        /// @brief Function that will handle the collision of the player
        /// @param entityId Entity (Player) id
        /// @param collisions Collision components
        /// @param transforms Transform components
        void playerCollisionCallback(const std::size_t &entityId,
            SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);
        /// @brief Function that will handle to move the parallax when quitting the screen
        void parallaxCollision(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);
        /// @brief Function that will handle the input callback
        void setInputCallback();
        /// @brief Function that will handle and update information about an input
        /// @param inputData Struct that will contain the information about the input
        void handleInput(struct GameEngine::Input::InputInfo inputData);
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
        bool _win;
        bool isOpen;
        bool _endScene;
        std::vector<GameEngine::Entity> _entities;
        RType::GameState _gameState;
        GameEngine::Input::InputType _lastInput;
        std::map<uint8_t, std::string> _listTextureTypePrefab;
        std::map<uint8_t, std::string> _listPathTextureId;
    };
} // namespace RType::Client

#endif /* !RTYPECLIENT_HPP_ */
