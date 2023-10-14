/*
** EPITECH PROJECT, 2023
** UdpServer.cpp
** File description:
** UdpServer
*/

#include "UdpServer.hpp"

RType::Server::UdpServer::UdpServer(
    asio::io_context &IOContext, unsigned short port, SafeQueue<std::string> &clientMessages)
    : GameEngine::Network::ACommunication(IOContext, port), _timer(IOContext), _timerTCP(IOContext),
      _signal(IOContext, SIGINT, SIGTERM), _clientsMessages(clientMessages)
{
    _signal.async_wait(std::bind(&asio::io_context::stop, &IOContext));
    indexPlayer = 0;
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ROOM),
        std::bind(&RType::Server::UdpServer::handleRoom, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::STRING),
        std::bind(&RType::Server::UdpServer::handleString, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::ENTITY),
        std::bind(&RType::Server::UdpServer::handleEntity, this, std::placeholders::_1));
    _commands.emplace(static_cast<uint8_t>(rtype::PacketType::CONNEXION),
        std::bind(&RType::Server::UdpServer::handleConnexion, this, std::placeholders::_1));
    readHeader();
    updateGameInfo();
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

void RType::Server::UdpServer::handleRoom(uint16_t size)
{
    struct rtype::Room room = Serialization::deserializeData<struct rtype::Room>(_buffer, size);

    std::cout << "----------" << std::endl;
    std::cout << "Room : " << std::endl;
    std::cout << "Id : " << room.id << " with " << static_cast<std::size_t>(room.slotsUsed) << "/"
              << static_cast<std::size_t>(room.slots) << " lefts." << std::endl;
    std::cout << "Stage level : " << room.stageLevel << std::endl;
    std::cout << "----------" << std::endl;
    _streamBuffer.consume(_streamBuffer.size());
    // std::cout << _message << std::endl;
}

void RType::Server::UdpServer::handleString(uint16_t size)
{
    std::vector<uint8_t> byteArrayToReceive = Serialization::deserializeData(_buffer, size);

    std::string message(byteArrayToReceive.begin(), byteArrayToReceive.end());
    // _message = message;
    std::cout << "Message : " << message << std::endl;
}

void RType::Server::UdpServer::handleEntity(uint16_t size)
{
    struct rtype::Entity entity = Serialization::deserializeData<struct rtype::Entity>(_buffer, size);

    _listPlayersInfos[entity.id] = entity;
    // if (_listPlayersInfos.find(entity.id) != _listPlayersInfos.end()) {
    // _listPlayersInfos. = entity;
    // } else
    // _list
    std::cout << "----------------" << std::endl;
    std::cout << "Entity number : " << entity.id << std::endl;
    std::cout << "Pos : " << entity.positionX << " - " << entity.positionY << std::endl;
    std::cout << "Direction : " << entity.directionX << " - " << entity.directionY << std::endl;
    std::cout << "LifePoint : " << entity.lifePoint << std::endl;
    std::cout << "----------------" << std::endl;
}

void RType::Server::UdpServer::handleConnexion(uint16_t size)
{
    struct rtype::Entity entity
    {
        .id = indexPlayer++, .positionX = 0, .positionY = 0, .directionX = 0, .directionY = 0, .lifePoint = 10,
    };

    _listPlayersInfos[entity.id] = entity;
}

std::map<unsigned short, asio::ip::udp::endpoint> RType::Server::UdpServer::getListClients() { return _listClient; }

void RType::Server::UdpServer::handleData(
    const asio::error_code &error, std::size_t, const struct rtype::HeaderDataPacket &header)
{
    if (!error) {
        std::cout << static_cast<std::size_t>(header.packetType) << std::endl;
        if (_commands.find(header.packetType) != _commands.end()) {
            std::cout << header.payloadSize << std::endl;
            _commands.at(header.packetType)(header.payloadSize);
        } else {
            std::cerr << "Packet Type doesn't exist !" << std::endl;
        }
        _streamBuffer.consume(header.payloadSize);
        readHeader();
    }
}

// void RType::Server::UdpServer::updateTCPInformation()
// {
//     std::string buff;

//     while (_clientsMessages.tryPop(buff)) {
//         for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
//             std::cout << "BUFF : " << buff;
//             if (buff == "Create Room\n") {
//                 struct rtype::Room room;
//                 // room.id = index;
//                 room.id = 0;
//                 room.slots = 4;
//                 room.slotsUsed = 4;
//                 room.stageLevel = 1;
//                 // _listRooms.insert({index, {"Room " + std::to_string(static_cast<std::size_t>(index)), room}});
//                 // std::cout << "Room " + std::to_string(static_cast<std::size_t>(index)) << std::endl;
//                 // sendData(Serialization::serializeData<struct rtype::Room>(room).data(),
//                 // Serialization::serializeData<struct rtype::Room>(room).size(),
//                 // static_cast<uint8_t>(rtype::PacketType::ROOM), _socket, client.second);
//                 // sendData(_listRooms.at(index).first.data(), _listRooms.at(index).first.size(),
//                 // static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
//             } else {
//                 buff.erase(std::remove(buff.begin(), buff.end(), '\0'), buff.end());
//                 sendData(
//                     buff.data(), buff.size(), static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
//             }
//         }
//     }
//     _timerTCP.expires_after(std::chrono::seconds(0));
//     _timerTCP.async_wait(std::bind(&RType::Server::UdpServer::updateTCPInformation, this));
// }

void RType::Server::UdpServer::broadcastInformation(/*SafeQueu<>*/)
{
    for (std::pair<unsigned short, asio::ip::udp::endpoint> client : _listClient) {
        for (std::pair<unsigned short, struct rtype::Entity> playerInfo : _listPlayersInfos) {
            std::vector<std::byte> playerInfoBinary =
                Serialization::serializeData<struct rtype::Entity>(playerInfo.second);
            sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(playerInfoBinary.data(), playerInfoBinary.size(),
                static_cast<uint8_t>(rtype::PacketType::ENTITY), _socket, client.second);
            _listPlayersInfos[playerInfo.second.id].lifePoint--;
        }
        // std::string message = "Sender endpoint : ";
        // message += client.second.address().to_string().c_str();
        // message += " on port : ";
        // message += client.second.address().to_string();
        // message += " ";
        // message += std::to_string(static_cast<int>(client.second.port()));
        // message += " with message : \n";

        // message.erase(std::remove(message.begin(), message.end(), '\0'), message.end());

        // // std::cout << message.data() << std::endl;
        // sendData<asio::ip::udp::socket, asio::ip::udp::endpoint>(
        //     message.data(), message.size(), static_cast<uint8_t>(rtype::PacketType::STRING), _socket, client.second);
    }
    updateGameInfo();
}

void RType::Server::UdpServer::updateGameInfo()
{
    _timer.expires_after(std::chrono::milliseconds(2000));
    _timer.async_wait(std::bind(&RType::Server::UdpServer::broadcastInformation, this));
}
