/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

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
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::CONNEXION),
        std::bind(&RType::Server::UdpServer::handleConnexion, this, std::placeholders::_1));
}

RType::Server::UdpServer::~UdpServer()
{
    std::string message = "Server down";
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
        sendData(
            message.data(), message.size(), static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
    }
    _socket.close();
}

void RType::Server::UdpServer::run() { readHeader(); }

void RType::Server::UdpServer::handleRoom(struct rtype::HeaderDataPacket header)
{
    struct rtype::Room room = Serialization::deserializeData<struct rtype::Room>(_buffer, header.payloadSize);

    std::cout << "----------" << std::endl;
    std::cout << "Room : " << std::endl;
    std::cout << "Id : " << room.id << " with " << static_cast<std::size_t>(room.slotsUsed) << "/"
              << static_cast<std::size_t>(room.slots) << " lefts." << std::endl;
    std::cout << "Stage level : " << room.stageLevel << std::endl;
    std::cout << "----------" << std::endl;
    // std::cout << _message << std::endl;
}

void RType::Server::UdpServer::handleString(struct rtype::HeaderDataPacket header)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(_buffer, header.payloadSize);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
    std::cout << "Message : " << message << std::endl;
}

void RType::Server::UdpServer::handleMove(struct rtype::HeaderDataPacket header)
{
    struct rtype::Move moveInfo = Serialization::deserializeData<struct rtype::Move>(_buffer, header.payloadSize);
    struct rtype::Event event;

    event.packetType = header.packetType;
    event.data = moveInfo;
    _eventQueue.push(event);
}

void RType::Server::UdpServer::handleEntity(struct rtype::HeaderDataPacket header)
{
    struct rtype::Entity entity = Serialization::deserializeData<struct rtype::Entity>(_buffer, header.payloadSize);

    _listPlayersInfos[entity.id] = entity;

    std::cout << "----------------" << std::endl;
    std::cout << "Entity number : " << entity.id << std::endl;
    std::cout << "Pos : " << entity.positionX << " - " << entity.positionY << std::endl;
    std::cout << "Direction : " << entity.directionX << " - " << entity.directionY << std::endl;
    std::cout << "----------------" << std::endl;
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

std::map<unsigned short, asio::ip::udp::endpoint> RType::Server::UdpServer::getListClients() { return _listClient; }

void RType::Server::UdpServer::handleData(
    const asio::error_code &error, std::size_t, const struct rtype::HeaderDataPacket &header)
{
    if (!error) {
        std::cout << static_cast<std::size_t>(header.packetType) << std::endl;
        if (_commands.find(header.packetType) != _commands.end()) {
            std::cout << header.payloadSize << std::endl;
            _commands.at(header.packetType)(header);
        } else {
            std::cerr << "Packet Type doesn't exist !" << std::endl;
        }
        _streamBuffer.consume(header.payloadSize);
        readHeader();
    }
}

void RType::Server::UdpServer::broadcastInformation(uint8_t packetType, std::vector<std::byte> dataToSend)
{
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
        sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(
            dataToSend.data(), dataToSend.size(), packetType, _socket, client.second);
    }
}
