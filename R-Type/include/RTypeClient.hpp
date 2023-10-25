/*
** EPITECH PROJECT, 2023
** RTypeClient.hpp
** File description:
** RTypeClient
*/

#ifndef RTYPECLIENT_HPP_
#define RTYPECLIENT_HPP_

#include "Protocol.hpp"
#include "UdpClient.hpp"
#include "TcpClient.hpp"
#include <asio.hpp>
#include "GameEngine.hpp"
#include "EntityManager.hpp"
#include <cstdint>

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
        /// @brief Function that will handle when new entity needed to be create
        /// @param event struct that will contain the information about the new entity
        void handleNewEntity(struct rtype::Event event);
        /// @brief Function that create a new Entity
        /// @param entity that will contain informations
        void entitySpawn(const struct rtype::Entity);
        /// @brief Function that will handle when entity needed to be update
        /// @param event struct that will contain the information about the entity
        void handleEntity(struct rtype::Event event);
        /// @brief Function that update a Entity
        /// @param entity update the corresponding entity
        void updateEntity(const struct rtype::Entity);
        /// @brief Function that will handle when entity needed to be delete
        /// @param event struct that will contain the information about the entity
        void handleDisconnexion(struct rtype::Event event);
        /// @brief Function that delete a Entity
        /// @param entity delete the corresponding entity
        void deleteEntity(const struct rtype::EntityId id);
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

        void setConnexionCallback();
        void setUpdateEntityCallback();
        void setDeleteEntityCallback();
        void setMovementEntityCallback();

        void runUdpServer();
        void runTcpServer();

      protected:
      private:
        std::size_t _findEntity(const std::size_t &networkId);
        bool _searchEntity(const std::size_t &networkId);

        GameEngine::GameEngine _gameEngine;
        asio::io_context _IOContext;
        asio::ip::udp::endpoint _serverUdpEndpoint;
        asio::ip::tcp::endpoint _serverTcpEndpoint;
        RType::Client::UdpClient _udpClient;
        // RType::Client::TcpClient _tcpClient;
        asio::signal_set _signal;
        SafeQueue<struct rtype::Event> _eventQueue;
        GameEngine::EntityManager _entityManager;
        bool _isRunning;
        bool _isPlayer;
        uint16_t _serverId;
        std::size_t _id;
    };
} // namespace RType::Client

#endif /* !RTYPECLIENT_HPP_ */
