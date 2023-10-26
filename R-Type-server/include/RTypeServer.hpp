/*
** EPITECH PROJECT, 2023
** RTypeServer.hpp
** File description:
** RTypeServer
*/

#ifndef RTYPESERVER_HPP_
#define RTYPESERVER_HPP_

#include "RType.hpp"
#include "SafeQueue.hpp"
#include "UdpServer.hpp"
#include "TcpServer.hpp"
#include "GameEngine.hpp"
#include <asio.hpp>
#include "EntityManager.hpp"
#include <map>

namespace RType::Server
{
    class RTypeServer
    {
      public:
        RTypeServer(unsigned short port = 8080);
        ~RTypeServer();
        /// @brief GameLoop to run the game
        void gameLoop();
        /// @brief Function that will handle every event from the udp server
        void handleEvent();
        /// @brief Function that will handle the connexion of a client
        void handleConnexion();
        /// @brief Function that will handle the move from a client
        /// @param event struct that contain the data (Information about the move)
        void handleMove(struct rtype::Event event);
        /// @brief Function that will handle the disconnexion of a client
        /// @param event struct that contain the data (information about the client)
        void handleDestroy(struct rtype::Event event);
        /// @brief Function that will start the Network in a thread
        /// @param isRunning boolean to know if the server is down
        void startNetwork(bool &isRunning);
        /// @brief Function that will brodcast informations to all clients
        void updateEntities();
        void handleShoot(struct rtype::Event event);

        void destroyShootCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);

      protected:
      private:
        GameEngine::GameEngine _gameEngine;
        asio::io_context _IOContext;
        asio::signal_set _signal;
        bool _isRunning;
        SafeQueue<std::string> _clientsMessages;
        RType::Server::UdpServer _udpServer;
        RType::Server::TcpServer _tcpServer;
        std::map<struct rtype::Room, std::map<unsigned short, struct rtype::Entity>> _listPlayersInfos;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClients;
        SafeQueue<struct rtype::Event> _eventQueue;
        GameEngine::EntityManager _entityManager;
        std::map<uint16_t, uint8_t> _listIdTexture;
        float pos;
    };
} // namespace RType::Server
#endif /* !RTYPESERVER_HPP_ */
