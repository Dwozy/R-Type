/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "Protocol.hpp"
#include "UdpServer.hpp"

RType::Server::UdpServer::UdpServer(
    asio::io_context &IOContext, unsigned short port, SafeQueue<struct rtype::Event> &eventQueue)
    : GameEngine::Network::ACommunication(IOContext, port), _timer(IOContext), _timerTCP(IOContext),
      _signal(IOContext, SIGINT, SIGTERM), _eventQueue(eventQueue)
{
    indexPlayer = 0;
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ROOM),
        std::bind(&RType::Server::UdpServer::handleRoom, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::STRING),
        std::bind(&RType::Server::UdpServer::handleString, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ENTITY),
        std::bind(&RType::Server::UdpServer::handleEntity, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::MOVE),
        std::bind(&RType::Server::UdpServer::handleMove, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::CONNEXION),
        std::bind(&RType::Server::UdpServer::handleConnexion, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::DISCONNEXION),
        std::bind(&RType::Server::UdpServer::handleDisconnexion, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::SHOOT),
        std::bind(&RType::Server::UdpServer::handleShoot, this, std::placeholders::_1));
}

RType::Server::UdpServer::~UdpServer()
{
    std::string message = "Server down";

    for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
        sendData(
            message.data(), message.size(), static_cast<uint8_t>(rtype::PacketType::STRING), _udpSocket, client.second);
    }
    _udpSocket.close();
}

void RType::Server::UdpServer::run() { readHeader(); }

void RType::Server::UdpServer::handleShoot(struct rtype::HeaderDataPacket header)
{
    auto shootInfo = Serialization::deserializeData<RType::Protocol::ShootData>(_streamBuffer, header.payloadSize);
    std::cout << "shoot at: x = " << shootInfo.x << " y = " << shootInfo.y << std::endl;

    struct rtype::Event event;

    event.packetType = header.packetType;
    event.data = shootInfo;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleRoom(struct rtype::HeaderDataPacket header)
{
    struct rtype::Room room = Serialization::deserializeData<struct rtype::Room>(_streamBuffer, header.payloadSize);
}

void RType::Server::UdpServer::handleString(struct rtype::HeaderDataPacket header)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(_streamBuffer, header.payloadSize);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
}

void RType::Server::UdpServer::handleMove(struct rtype::HeaderDataPacket header)
{
    auto moveInfo = Serialization::deserializeData<RType::Protocol::MoveData>(_streamBuffer, header.payloadSize);
    struct rtype::Event event;

    event.packetType = header.packetType;
    event.data = moveInfo;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleDisconnexion(struct rtype::HeaderDataPacket header)
{
    struct rtype::EntityId entity =
        Serialization::deserializeData<struct rtype::EntityId>(_streamBuffer, header.payloadSize);
    struct rtype::Event event;

    std::cout << "Disconnexion" << std::endl;
    event.packetType = header.packetType;
    event.data = entity;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleEntity(struct rtype::HeaderDataPacket header)
{
    struct rtype::Entity entity =
        Serialization::deserializeData<struct rtype::Entity>(_streamBuffer, header.payloadSize);

    _listPlayersInfos[entity.id] = entity;
}

void RType::Server::UdpServer::handleConnexion(struct rtype::HeaderDataPacket header)
{
    struct rtype::Event event = {};

    struct rtype::Entity entity = {indexPlayer, 0, 0, 0, 0};
    _listPlayersInfos[entity.id] = entity;
    indexPlayer++;

    event.packetType = header.packetType;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleData(struct rtype::HeaderDataPacket &header)
{
    if (_commands.find(header.packetType) != _commands.end()) {
        _commands.at(header.packetType)(header);
    } else {
        std::cerr << "Packet Type doesn't exist !" << std::endl;
    }
}

void RType::Server::UdpServer::broadcastInformation(uint8_t packetType, std::vector<std::byte> dataToSend)
{
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
        sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(
            dataToSend.data(), dataToSend.size(), packetType, _udpSocket, client.second);
    }
}
