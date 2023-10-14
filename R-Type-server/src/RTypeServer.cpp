/*
** EPITECH PROJECT, 2023
** RTypeServer.cpp
** File description:
** RTypeServer
*/

#include "RTypeServer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"

RType::Server::RTypeServer::RTypeServer(unsigned short port)
    : _signal(_IOContext, SIGINT, SIGTERM), _udpServer(_IOContext, port, std::ref(_clientsMessages))
{
    gameLoop();
}

RType::Server::RTypeServer::~RTypeServer() {}

void RType::Server::RTypeServer::gameLoop()
{
    while (!_IOContext.stopped()) {

        _IOContext.run_one();
    }
}
