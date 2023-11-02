/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "Protocol.hpp"
#include "UdpServer.hpp"

RType::Server::UdpServer::UdpServer(
    asio::io_context &IOContext, unsigned short port, SafeQueue<struct RType::Event> &eventQueue)
    : GameEngine::Network::ACommunication(IOContext, port), _timer(IOContext), _timerTCP(IOContext),
      _signal(IOContext, SIGINT, SIGTERM), _eventQueue(eventQueue)
{
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_RES),
        std::bind(
            &RType::Server::UdpServer::handleTextureResponse, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION_RES),
        std::bind(
            &RType::Server::UdpServer::handleCollisionResponse, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::INPUT),
        std::bind(&RType::Server::UdpServer::handleInput, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::PacketType::STRING),
        std::bind(&RType::Server::UdpServer::handleString, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::PacketType::CONNEXION),
        std::bind(&RType::Server::UdpServer::handleConnexion, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::PacketType::DESTROY),
        std::bind(&RType::Server::UdpServer::handleDisconnexion, this, std::placeholders::_1, std::placeholders::_2));
}

RType::Server::UdpServer::~UdpServer()
{
    std::string message = "Server down";

    for (auto endpoint : _listClient) {
        sendData(message.data(), message.size(), static_cast<uint8_t>(RType::PacketType::STRING), _udpSocket,
            endpoint.second);
    }
    _udpSocket.close();
}

void RType::Server::UdpServer::run() { readHeader(); }

void RType::Server::UdpServer::handleInput(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    auto inputInfo = Serialization::deserializeData<RType::Protocol::InputData>(_streamBuffer, header.payloadSize);

    struct RType::Event event;

    event.packetType = header.packetType;
    event.data = inputInfo;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleTextureResponse(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::TextureResponse response =
        Serialization::deserializeData<RType::Protocol::TextureResponse>(_streamBuffer, header.payloadSize);
    struct RType::Event event;

    event.packetType = header.packetType;
    event.data = response;
    event.port = port;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleCollisionResponse(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::CollisionResponse response =
        Serialization::deserializeData<RType::Protocol::CollisionResponse>(_streamBuffer, header.payloadSize);
    struct RType::Event event;

    event.packetType = header.packetType;
    event.data = response;
    event.port = port;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleString(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(_streamBuffer, header.payloadSize);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
}

void RType::Server::UdpServer::handleDisconnexion(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::EntityIdData entity =
        Serialization::deserializeData<struct RType::Protocol::EntityIdData>(_streamBuffer, header.payloadSize);
    struct RType::Event event;

    event.packetType = header.packetType;
    event.data = entity;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleConnexion(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Event event;

    event.packetType = header.packetType;
    event.port = port;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleData(struct RType::Protocol::HeaderDataPacket &header, unsigned short port)
{
    if (_commands.find(header.packetType) != _commands.end())
        _commands.at(header.packetType)(header, port);
    else
        std::cerr << "Packet Type doesn't exist !" << std::endl;
}

std::map<unsigned short, asio::ip::udp::endpoint> RType::Server::UdpServer::getListClients() { return _listClient; }

void RType::Server::UdpServer::sendInformation(
    uint8_t packetType, std::vector<std::byte> dataToSend, asio::ip::udp::endpoint &endpoint)
{
    sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(
        dataToSend.data(), dataToSend.size(), packetType, _udpSocket, endpoint);
}
