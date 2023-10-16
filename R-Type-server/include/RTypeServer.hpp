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
#include "GameEngineServer.hpp"
#include <asio.hpp>

namespace RType::Server
{
    class RTypeServer
    {
      public:
        RTypeServer(unsigned short port = 8080);
        ~RTypeServer();

        void gameLoop();

        void communication(RType::Server::UdpServer &udpserver);

        void handleEvent();
        void handleConnexion();
        void startNetwork(bool &isRunning);
        void updateEntities();
        void setPlayerEntity(float posX, float posY, GameEngine::Entity entity, GameEngine::Registry &registry);

        // void collisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            // SparseArray<GameEngine::TransformComponent> &transforms);

      protected:
      private:
        GameEngine::GameEngineServer _gameEngine;
        asio::io_context _IOContext;
        asio::signal_set _signal;
        bool _isRunning;
        SafeQueue<std::string> _clientsMessages;
        RType::Server::UdpServer _udpServer;
        std::map<struct rtype::Room, std::map<unsigned short, struct rtype::Entity>> _listPlayersInfos;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClients;
        std::vector<GameEngine::Entity> _listEntities;
        SafeQueue<struct rtype::Event> _eventQueue;
    };
} // namespace RType::Server
#endif /* !RTYPESERVER_HPP_ */
