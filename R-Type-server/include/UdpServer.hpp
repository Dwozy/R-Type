/*
** EPITECH PROJECT, 2023
** UdpServer.hpp
** File description:
** UdpServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "Network/ACommunication.hpp"
#include "RType.hpp"
#include "SafeQueue.hpp"
#include "Network/Serialization.hpp"
#include <array>
#include <asio.hpp>
#include <iostream>
#include <map>
#include "Entity.hpp"
#include "Protocol.hpp"

namespace RType::Server
{
    /// @brief UdpServer Class that create a UDP server that client can connect
    /// to communicate
    class UdpServer : public GameEngine::Network::ACommunication
    {
      public:
        UdpServer(asio::io_context &IOContext, unsigned short port, SafeQueue<struct RType::Event> &eventQueue);
        ~UdpServer();

        /// @brief Handle the data depends of the header
        /// @param error if asynchronous operation fails, it will be checked
        /// @param header that contain the type of data
        void handleData(struct RType::Protocol::HeaderDataPacket &header, unsigned short port);
        /// @brief Function that will send informations to connected clients
        /// @param packetType the type of data that will be send
        /// @param dataToSend that will be send to clients
        void sendInformation(uint8_t packetType, std::vector<std::byte> dataToSend, asio::ip::udp::endpoint &endpoint);
        /// @brief Handle String that will be retrieve and push a event
        /// @param header that contains the size of the payload
        /// @param port corresponging to the port of the client that send the message
        void handleString(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Handle Connexion that will be retrieve and push a event
        /// @param header that contains the size of the payload
        /// @param port corresponging to the port of the client that send the message
        void handleConnexion(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Handle Disconnexion that will be retrieve and push a event
        /// @param header that contains the size of the payload
        /// @param port corresponging to the port of the client that send the message
        void handleDisconnexion(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Start the UDP Server
        void run();
        /// @brief Handle Texture response that will be retrieve and push a event
        /// @param header that contains the size of the payload
        /// @param port corresponging to the port of the client that send the message
        void handleTextureResponse(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Handle Collision response that will be retrieve and push a event
        /// @param header that contains the size of the payload
        /// @param port corresponging to the port of the client that send the message
        void handleCollisionResponse(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Handle Input response that will be retrieve and push a event
        /// @param header that contains the size of the payload
        /// @param port corresponging to the port of the client that send the message
        void handleInput(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Function that will return all of the clients endpoint
        /// @return list of all clients endpoints
        std::map<unsigned short, asio::ip::udp::endpoint> &getListClients();

      protected:
      private:
        unsigned short indexPlayer;
        asio::steady_timer _timer;
        asio::steady_timer _timerTCP;
        asio::signal_set _signal;
        SafeQueue<struct RType::Event> &_eventQueue;
        asio::ip::udp::endpoint _clientEndpoint;
        std::unordered_map<uint8_t, std::function<void(struct RType::Protocol::HeaderDataPacket, unsigned port)>>
            _commands;
    };
} // namespace RType::Server
#endif /* !UDPSERVER_HPP_ */
