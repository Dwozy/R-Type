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
        /// @brief Function that will handle a shoot event
        /// @param shootInfo Struct that will contain the information about the shoot
        void handleShoot(struct RType::Protocol::ShootData shootInfo);
        /// @brief Function that will spawn enemies from regulat intervals
        /// @param now Information about the timer at Nth time
        void spawnMob(std::chrono::steady_clock::time_point &now);
        /// @brief Function that will be update all informations of the game to the clients
        void broadcastInformation();
        /// @brief Function that will handle the damage
        /// @param entityId Entity (Player)
        /// @param i the index of the component
        /// @param collisions Game engine Collision component
        void handlingDamage(
            std::size_t entityId, std::size_t i, SparseArray<GameEngine::CollisionComponent> &collisions);
        /// @brief Function that will handle the destory of a entity
        /// @param entityId Entity
        /// @param collisions Game engine Collision component
        /// @param transforms Game engine transform component
        void destroyEntityCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);
        /// @brief Function that will handle the replacing of player position
        /// @param entityId Entity (Player)
        /// @param collisions Game engine  collision component
        /// @param transforms Game engine  Information component
        void playerCollisionCallback(const std::size_t &entityId,
            SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);
        /// @brief Function that will handle the damage information to the health
        /// @param entityId Entity id (Player)
        /// @param collisions Game engine collision
        /// @param transforms Game engine transforms
        void playerDamageCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
            SparseArray<GameEngine::TransformComponent> &transforms);
        /// @brief Function that will be update all informations about every transform component to the clients
        void broadcastTransformComponent();
        /// @brief Function that will send the transform information to a specific client
        /// @param id Id of the entity
        /// @param position Position of the entity
        /// @param velocity Velocity of the entity
        /// @param endpoint Endpoint of the client
        void sendTransformComponent(uint16_t id, GameEngine::Vector2<float> position,
            GameEngine::Vector2<float> velocity, asio::ip::udp::endpoint &endpoint);
        /// @brief Function that will be update all informations about every collision component to the clients
        void broadcastCollisionComponent();
        /// @brief Function that will send the collision information to a specific client
        /// @param id Id of the entity
        /// @param collider Rect collider of the collision
        /// @param layer Layer of the entity
        /// @param endpoint Endpoint of the client
        void sendCollisionComponent(
            uint16_t id, GameEngine::Rectf collider, std::size_t layer, asio::ip::udp::endpoint &endpoint);
        /// @brief Function that will be update all informations about every texture component to the clients
        void broadcastTextureComponent();
        /// @brief Function that will send the texture information to a specific client
        /// @param id Id of the entity
        /// @param index Index of the texture rect
        /// @param texture Texture component
        /// @param endpoint Endpoint of the client
        void sendTextureComponent(
            uint16_t id, std::size_t index, GameEngine::TextureComponent &texture, asio::ip::udp::endpoint &endpoint);
        /// @brief Function that will handle the texture component response from the client
        /// @param event Struct that will contain the information about the texture index
        void handleTextureResponse(struct RType::Event event);
        /// @brief Function that will handle the collision component response from the client
        /// @param event Struct that will contain the information about the collision
        void handleCollisionResponse(struct RType::Event event);
        /// @brief Function that will handle the input from the client
        /// @param event Struct that will contain the input information received
        void handleInput(struct RType::Event event);
        /// @brief Function that will set a new entity information that needed to be send
        /// @return a component list information about its texture, transform and collision
        componentList setEntitiesComponent();
        /// @brief Function that broadcast information to all the clients about a entity
        /// @param entity Specific entity that need to be send
        void broadcastEntityInformation(const GameEngine::Entity &entity);
        /// @brief Function that check if the texture need to be send to a specific client
        /// @param listDisplayTexture Vector that will decide if the texture is already set from the client
        /// @param entity Entity
        /// @param endpoint Endpoint of the client
        void checkSendingTexture(
            std::vector<bool> listDisplayTexture, const GameEngine::Entity &entity, asio::ip::udp::endpoint &endpoint);
        /// @brief Set Game engine component for the server
        void setGameEngineComponent();
        /// @brief Set the prefab, by loading, that will be used in the server
        void setPrefab();
        /// @brief Set Game engine system
        void setGameEngineSystem();
        /// @brief Set Game engine information
        void setGameEngine();
        /// @brief Set up the game from the server
        void setupGame();
        /// @brief Function that will handle the differents timers for the game
        void handlingTimers();
        /// @brief Function that will handle the endgame
        void handlingEndGame();
        /// @brief Set the timers needed for the game
        void setTimers();
        std::size_t findEntity(const std::size_t &networkId);
        bool searchEntity(const std::size_t &networkId);
        /// @brief Function that will send information about the controllable component to a specific client
        /// @param entity Entity that will be set the controlalble
        /// @param port Port of the client
        void sendControllableInformation(GameEngine::Entity &entity, unsigned short port);
        /// @brief Function that check if the collision component need to be send to the client
        /// @param collision Collision component
        /// @param i Index of the component
        void checkCollisionComponent(GameEngine::CollisionComponent &collision, std::size_t i);
        /// @brief Function that will handle the different of shoot (Charged, simple...)
        /// @param typeShootString The shoot type that will be used for creating the entity from the prefab
        /// @param shootData Struct that will contain information about the shoot
        /// @param typeShoot Enum that describe which shoot is set
        void handleShootType(const std::string &typeShootString, struct RType::Protocol::ShootData shootData,
            RType::TextureType typeShoot);
        /// @brief Function that will update all components when a new entity is created
        /// @param entity Entity that need to be update
        /// @param entityType Type of the entity (Player, Mob, Shoot...)
        void updateComponentInformation(GameEngine::Entity &entity, RType::TextureType entityType);
        /// @brief Function that will handle the life point of every player
        /// @param entityId Entity id that is need to find which entity lose life point
        /// @param id Entity that collide to the first entity and need to process damage
        void handlingLifePoint(std::size_t entityId, std::size_t id);
        /// @brief Function that will handle the movement of a entity
        /// @param transform Game engine transform
        /// @param inputInfo Struct that will contain the input information
        /// @return a vector that correspond to the new movement a the entity
        GameEngine::Vector2<float> handlingMovement(
            GameEngine::TransformComponent &transform, struct RType::Protocol::InputData inputInfo);
        /// @brief Function that will handle and publish a event to destroy a specific entity
        /// @param id Id of the entity that need to be delete
        void handleDestroyCallback(std::size_t &id);
        /// @brief Set the destroy callback
        void setDestroyCallback();
        /// @brief Set all of the callback needed to be use in the server Game engine
        void setGameEngineCallback();
        /// @brief Function that will spawn differents types, depending of the timing
        /// @param mob String that correspond to the entity that will be need to create from a prefab
        /// @param mobType Enum describing the type of the mob
        void spawnEntityMob(const std::string &mob, RType::TextureType mobType);
        /// @brief Function that will set the invincibility of a player when taking damage
        /// @param now Information of the timer at Nth time
        void handleImmunity(std::chrono::steady_clock::time_point &now);
        /// @brief Function that will send the score to a specific client when the score changed
        /// @param port corresponding of the client port
        void sendScore(unsigned short port);
        void setImmunity(std::chrono::duration<float> timerInvincibility,
            std::pair<const uint16_t, std::pair<bool, std::chrono::steady_clock::time_point>> playerTimer,
            std::chrono::steady_clock::time_point &now);
        /// @brief Function that will send the destroy entity information
        /// @param entity Entity that will be destroyed
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
        std::map<uint16_t, uint8_t> _listIndexTexture;
        std::map<unsigned short, componentList> _listInfosComponent;
        std::map<std::string, std::chrono::steady_clock::time_point> _timers;
        std::map<uint16_t, std::pair<bool, std::chrono::steady_clock::time_point>> _timerLifePoint;
        std::vector<std::size_t> _nbPlayerTexture;
        std::map<uint16_t, std::pair<bool, std::chrono::steady_clock::time_point>> _chargedAttackTimer;
        std::size_t _nbPlayers;
        bool _chargedAttack;
        bool _killEnemy;
        std::size_t _points;
        std::vector<uint8_t> _inputsType;
    };
} // namespace RType::Server
#endif /* !RTYPESERVER_HPP_ */
