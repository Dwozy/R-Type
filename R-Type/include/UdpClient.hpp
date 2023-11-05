/*
** EPITECH PROJECT, 2023
** UdpClient.hpp
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "Network/ACommunication.hpp"
#include "RType.hpp"
#include "Network/Serialization.hpp"
#include <asio.hpp>
#include <iostream>
#include "SafeQueue.hpp"

namespace RType::Client
{
    class UdpClient : public GameEngine::Network::ACommunication
    {
      public:
        UdpClient(asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint,
            SafeQueue<struct RType::Event> &eventQueue);
        ~UdpClient();

        void handleTransformComponent(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        void handleTextureComponent(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        void handleCollisionComponent(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        void handleControllableComponent(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        void handleTextureState(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        void handleScore(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        void handleEndGame(struct RType::Protocol::HeaderDataPacket header, unsigned short port);

        /// @brief Handle String
        /// @param header that contains the size of the payload
        void handleString(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Handle Disconnexion
        /// @param header that contains the size of the payload
        void handleDisconnexion(struct RType::Protocol::HeaderDataPacket header, unsigned short port);
        /// @brief Function that will send information to the server
        /// @param dataInformation that contains the information
        /// @param packetType corresponding the type of data
        void sendDataInformation(std::vector<std::byte> dataInformation, uint8_t packetType);
        /// @brief Launch the Udp Client
        void run();
        /// @brief Handle the data depends of the header
        /// @param error if asynchronous operation fails, it will be checked
        /// @param header that contain the type of data
        void handleData(struct RType::Protocol::HeaderDataPacket &, unsigned short port);

      protected:
      private:
        asio::io_context &_IOContext;
        asio::ip::udp::endpoint &_serverEndpoint;
        std::unordered_map<uint8_t,
            std::function<void(struct RType::Protocol::HeaderDataPacket header, unsigned short port)>>
            _commands;
        SafeQueue<struct RType::Event> &_eventQueue;
    };
} // namespace RType::Client
#endif /* !UDPCLIENT_HPP_ */
