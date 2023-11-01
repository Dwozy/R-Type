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
#include <map>
#include "Protocol.hpp"

using componentList = std::map<std::size_t, std::map<RType::Protocol::ComponentType, std::vector<bool>>>;

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
        void handleConnexion(struct rtype::Event event);
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

        void spawnMob();

        void broadcastInformation();

        void destroyEntityCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);

        void playerCollisionCallback(const std::size_t &entityId,
            SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);

        void playerDamageCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);

        void broadcastTransformComponent();
        void sendTransformComponent(uint16_t id, GameEngine::Vector2<float> position,
            GameEngine::Vector2<float> velocity, asio::ip::udp::endpoint &endpoint);

        void broadcastCollisionComponent();
        void sendCollisionComponent(
            uint16_t id, GameEngine::Rectf collider, std::size_t layer, asio::ip::udp::endpoint &endpoint);

        void broadcastTextureComponent();

        void sendTextureComponent(
            uint16_t id, std::size_t index, GameEngine::TextureComponent texture, asio::ip::udp::endpoint &endpoint);

        void handleTextureResponse(struct rtype::Event event);
        void handleCollisionResponse(struct rtype::Event event);

        componentList setEntitiesComponent();

        void broadcastEntityInformation(const GameEngine::Entity &entity);

        void checkSendingTexture(
            std::vector<bool> listDisplayTexture, const GameEngine::Entity &entity, asio::ip::udp::endpoint &endpoint);

        void setGameEngineComponent();
        void setPrefab();
        void setGameEngineSystem();
        void setGameEngine();
        void setupGame();

      protected:
      private:
        GameEngine::GameEngine _gameEngine;
        asio::io_context _IOContext;
        asio::signal_set _signal;
        bool _isRunning;
        RType::Server::UdpServer _udpServer;
        RType::Server::TcpServer _tcpServer;
        std::map<struct rtype::Room, std::map<unsigned short, struct rtype::Entity>> _listPlayersInfos;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClients;
        SafeQueue<struct rtype::Event> _eventQueue;
        std::map<uint16_t, uint8_t> _listIdType;
        std::map<uint16_t, uint8_t> _listLifePoints;
        std::map<unsigned short, componentList> _listInfosComponent;
        std::size_t _nbPlayers;
        float pos;
    };
} // namespace RType::Server
#endif /* !RTYPESERVER_HPP_ */
