/*
** EPITECH PROJECT, 2023
** Udpcpp
** File description:
** UdpClient
*/

#include "UdpClient.hpp"
#include "Protocol.hpp"

RType::Client::UdpClient::UdpClient(
    asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint, SafeQueue<struct rtype::Event> &eventQueue)
    : ACommunication(IOContext, 0), _IOContext(IOContext), _serverEndpoint(serverEndpoint), _eventQueue(eventQueue)
{
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::TRANSFORM),
        std::bind(&RType::Client::UdpClient::handleTransformComponent, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE),
        std::bind(&RType::Client::UdpClient::handleTextureComponent, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION),
        std::bind(&RType::Client::UdpClient::handleCollisionComponent, this, std::placeholders::_1));



    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::STRING),
        std::bind(&RType::Client::UdpClient::handleString, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ENTITY),
        std::bind(&RType::Client::UdpClient::handleEntity, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::CONNECTED),
        std::bind(&RType::Client::UdpClient::handleConnexionSuccess, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::DESTROY),
        std::bind(&RType::Client::UdpClient::handleDisconnexion, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::SHOOT),
        std::bind(&RType::Client::UdpClient::handleShoot, this, std::placeholders::_1));
}

RType::Client::UdpClient::~UdpClient() { _udpSocket.close(); }

void RType::Client::UdpClient::handleShoot(struct rtype::HeaderDataPacket header)
{
    struct rtype::Shoot shoot = Serialization::deserializeData<struct rtype::Shoot>(_streamBuffer, header.payloadSize);
    struct rtype::Event event = {.packetType = header.packetType, .data = shoot};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleTransformComponent(struct rtype::HeaderDataPacket header)
{
    struct RType::Protocol::TransformData transformData =
        Serialization::deserializeData<struct RType::Protocol::TransformData>(_streamBuffer, header.payloadSize);
    struct rtype::Event event = {.packetType = header.packetType, .data = transformData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleTextureComponent(struct rtype::HeaderDataPacket header)
{
    struct RType::Protocol::TextureData textureData =
        Serialization::deserializeData<struct RType::Protocol::TextureData>(_streamBuffer, header.payloadSize);
    struct rtype::Event event = {.packetType = header.packetType, .data = textureData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleCollisionComponent(struct rtype::HeaderDataPacket header)
{
    struct RType::Protocol::CollisionData collisionData =
        Serialization::deserializeData<struct RType::Protocol::CollisionData>(_streamBuffer, header.payloadSize);
    struct rtype::Event event = {.packetType = header.packetType, .data = collisionData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleString(struct rtype::HeaderDataPacket header)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(_streamBuffer, header.payloadSize);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
    if (message == "Server down" || message == "You lose" || message == "You win") {
        if (message != "Server down")
            std::cout << message << std::endl;
        _IOContext.stop();
    }
}

void RType::Client::UdpClient::handleEntity(struct rtype::HeaderDataPacket header)
{
    struct rtype::Entity entity =
        Serialization::deserializeData<struct rtype::Entity>(_streamBuffer, header.payloadSize);
    struct rtype::Event event = {.packetType = header.packetType, .data = entity};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleConnexionSuccess(struct rtype::HeaderDataPacket header)
{
    struct rtype::Entity entity =
        Serialization::deserializeData<struct rtype::Entity>(_streamBuffer, header.payloadSize);
    struct rtype::Event event = {.packetType = header.packetType, .data = entity};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleDisconnexion(struct rtype::HeaderDataPacket header)
{
    struct rtype::EntityId entity =
        Serialization::deserializeData<struct rtype::EntityId>(_streamBuffer, header.payloadSize);
    struct rtype::Event event = {.packetType = header.packetType, .data = entity};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleData(struct rtype::HeaderDataPacket &header)
{
    if (_commands.find(header.packetType) != _commands.end())
        _commands.at(header.packetType)(header);
    else
        std::cerr << "Packet Type doesn't exist !" << std::endl;
}

void RType::Client::UdpClient::sendDataInformation(std::vector<std::byte> dataInformation, uint8_t packetType)
{
    sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(
        dataInformation.data(), dataInformation.size(), packetType, _udpSocket, _serverEndpoint);
}

void RType::Client::UdpClient::run()
{
    sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(
        0, 0, static_cast<uint8_t>(rtype::PacketType::CONNEXION), _udpSocket, _serverEndpoint);
    readHeader();
}
