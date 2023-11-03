/*
** EPITECH PROJECT, 2023
** Udpcpp
** File description:
** UdpClient
*/

#include "UdpClient.hpp"
#include "Protocol.hpp"

RType::Client::UdpClient::UdpClient(
    asio::io_context &IOContext, asio::ip::udp::endpoint &serverEndpoint, SafeQueue<struct RType::Event> &eventQueue)
    : ACommunication(IOContext, 0), _IOContext(IOContext), _serverEndpoint(serverEndpoint), _eventQueue(eventQueue)
{
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::TRANSFORM),
        std::bind(
            &RType::Client::UdpClient::handleTransformComponent, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE),
        std::bind(
            &RType::Client::UdpClient::handleTextureComponent, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION),
        std::bind(
            &RType::Client::UdpClient::handleCollisionComponent, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::CONTROLLABLE),
        std::bind(&RType::Client::UdpClient::handleControllableComponent, this, std::placeholders::_1,
            std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_STATE),
        std::bind(&RType::Client::UdpClient::handleTextureState, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::PacketType::STRING),
        std::bind(&RType::Client::UdpClient::handleString, this, std::placeholders::_1, std::placeholders::_2));
    _commands.emplace(static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY),
        std::bind(&RType::Client::UdpClient::handleDisconnexion, this, std::placeholders::_1, std::placeholders::_2));
}

RType::Client::UdpClient::~UdpClient() { _udpSocket.close(); }

void RType::Client::UdpClient::handleControllableComponent(
    struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::ControllableData controllableData =
        Serialization::deserializeData<struct RType::Protocol::ControllableData>(_streamBuffer, header.payloadSize);
    struct RType::Event event = {.packetType = header.packetType, .data = controllableData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleTransformComponent(
    struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::TransformData transformData =
        Serialization::deserializeData<struct RType::Protocol::TransformData>(_streamBuffer, header.payloadSize);
    struct RType::Event event = {.packetType = header.packetType, .data = transformData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleTextureState(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::StatePlayerData stateData =
        Serialization::deserializeData<struct RType::Protocol::StatePlayerData>(_streamBuffer, header.payloadSize);
    struct RType::Event event = {.packetType = header.packetType, .data = stateData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleTextureComponent(
    struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::TextureData textureData =
        Serialization::deserializeData<struct RType::Protocol::TextureData>(_streamBuffer, header.payloadSize);
    struct RType::Event event = {.packetType = header.packetType, .data = textureData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleCollisionComponent(
    struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::CollisionData collisionData =
        Serialization::deserializeData<struct RType::Protocol::CollisionData>(_streamBuffer, header.payloadSize);
    struct RType::Event event = {.packetType = header.packetType, .data = collisionData};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleString(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(_streamBuffer, header.payloadSize);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
    if (message == "Server down" || message == "You lose" || message == "You win") {
        if (message != "Server down")
            std::cout << message << std::endl;
        _IOContext.stop();
    }
}

void RType::Client::UdpClient::handleDisconnexion(struct RType::Protocol::HeaderDataPacket header, unsigned short port)
{
    struct RType::Protocol::EntityIdData entity =
        Serialization::deserializeData<struct RType::Protocol::EntityIdData>(_streamBuffer, header.payloadSize);
    struct RType::Event event = {.packetType = header.packetType, .data = entity};

    _eventQueue.push(event);
}

void RType::Client::UdpClient::handleData(struct RType::Protocol::HeaderDataPacket &header, unsigned short port)
{
    if (_commands.find(header.packetType) != _commands.end())
        _commands.at(header.packetType)(header, port);
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
        0, 0, static_cast<uint8_t>(RType::Protocol::PacketType::CONNEXION), _udpSocket, _serverEndpoint);
    readHeader();
}
