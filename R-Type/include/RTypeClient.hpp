/*
** EPITECH PROJECT, 2023
** RTypeClient.hpp
** File description:
** RTypeClient
*/

#ifndef RTYPECLIENT_HPP_
#define RTYPECLIENT_HPP_

#include "UdpClient.hpp"
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

        void startNetwork(bool &isRunning);
        void gameLoop();
        void handleEvent();

        void handleNewEntity(struct rtype::Event event);
        void entitySpawn(const struct rtype::Entity);

        void handleEntity(struct rtype::Event event);
        void updateEntity(const struct rtype::Entity);

        void handleDisconnexion(struct rtype::Event event);
        void deleteEntity(const struct rtype::EntityId id);

        void handleQuitClient();

      protected:
      private:
        GameEngine::GameEngine _gameEngine;
        asio::io_context _IOContext;
        asio::ip::udp::endpoint _serverUdpEndpoint;
        RType::Client::UdpClient _udpClient;
        asio::signal_set _signal;
        SafeQueue<struct rtype::Event> _eventQueue;
        GameEngine::EntityManager _entityManager;
        bool _isRunning;
        bool _isPlayer;
        uint16_t _id;
    };
} // namespace RType::Client

#endif /* !RTYPECLIENT_HPP_ */
