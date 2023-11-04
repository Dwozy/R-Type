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
        void handleConnexion(struct RType::Event event);
        /// @brief Function that will handle the move from a client
        /// @param event struct that contain the data (Information about the move)
        void handleMove(struct RType::Protocol::MoveData moveInfo);
        /// @brief Function that will handle the disconnexion of a client
        /// @param event struct that contain the data (information about the client)
        void handleDestroy(struct RType::Event event);
        /// @brief Function that will start the Network in a thread
        /// @param isRunning boolean to know if the server is down
        void startNetwork(bool &isRunning);

        void handleShoot(struct RType::Protocol::ShootData shootInfo);
        void spawnMob(std::chrono::steady_clock::time_point &now);

        void broadcastInformation();

        void handlingDamage(
            std::size_t entityId, std::size_t i, SparseArray<GameEngine::CollisionComponent> &collisions);

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

        void handleTextureResponse(struct RType::Event event);
        void handleCollisionResponse(struct RType::Event event);
        void handleInput(struct RType::Event event);

        componentList setEntitiesComponent();

        void broadcastEntityInformation(const GameEngine::Entity &entity);

        void checkSendingTexture(
            std::vector<bool> listDisplayTexture, const GameEngine::Entity &entity, asio::ip::udp::endpoint &endpoint);

        void setGameEngineComponent();
        void setPrefab();
        void setGameEngineSystem();
        void setGameEngine();
        void setupGame();
        void handlingTimers();
        void handlingEndGame();
        void setTimers();

        std::size_t findEntity(const std::size_t &networkId);
        bool searchEntity(const std::size_t &networkId);

        void sendControllableInformation(GameEngine::Entity &entity, unsigned short port);

        void checkCollisionComponent(GameEngine::CollisionComponent &collision, std::size_t i);

        void handleShootType(const std::string &typeShootString, struct RType::Protocol::ShootData shootData,
            RType::TextureType typeShoot);
        void updateComponentInformation(GameEngine::Entity &entity, RType::TextureType entityType);

        void handlingLifePoint(std::size_t entityId, std::size_t id);

        GameEngine::Vector2<float> handlingMovement(
            GameEngine::TransformComponent &transform, struct RType::Protocol::InputData inputInfo);

        void handleDestroyCallback(std::size_t &id);
        void setDestroyCallback();
        void setGameEngineCallback();

        void spawnEntityMob(const std::string &mob, RType::TextureType mobType);
        void handleImmunity(std::chrono::steady_clock::time_point &now);
        void sendScore(unsigned short port);

        void setImmunity(std::chrono::duration<float> timerInvincibility,
            std::pair<const uint16_t, std::pair<bool, std::chrono::steady_clock::time_point>> playerTimer,
            std::chrono::steady_clock::time_point &now);

        void sendDestroyInfo(struct RType::Protocol::EntityIdData entity);

      protected:
      private:
        GameEngine::GameEngine _gameEngine;
        asio::io_context _IOContext;
        asio::signal_set _signal;
        bool _isRunning;
        RType::Server::UdpServer _udpServer;
        std::map<unsigned short, asio::ip::udp::endpoint> _listClients;
        SafeQueue<struct RType::Event> _eventQueue;
        std::map<uint16_t, uint8_t> _listIdType;
        std::map<uint16_t, uint8_t> _listLifePoints;
        std::map<unsigned short, componentList> _listInfosComponent;
        std::map<std::string, std::chrono::steady_clock::time_point> _timers;
        std::map<uint16_t, std::pair<bool, std::chrono::steady_clock::time_point>> _timerLifePoint;
        std::size_t _nbPlayers;
        bool _chargedAttack;
        bool _killEnemy;
        std::size_t _points;
        std::vector<uint8_t> _inputsType;
    };
} // namespace RType::Server
#endif /* !RTYPESERVER_HPP_ */
