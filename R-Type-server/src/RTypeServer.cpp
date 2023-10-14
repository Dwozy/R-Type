/*
** EPITECH PROJECT, 2023
** RTypeServer.cpp
** File description:
** RTypeServer
*/

#include "RTypeServer.hpp"

RType::Server::RTypeServer::RTypeServer(unsigned short port):
    _signal(_IOContext, SIGINT, SIGTERM),
    _udpServer(_IOContext, port, std::ref(_clientsMessages))
{
    // std::thread gameLoop(&RType::Server::RTypeServer::gameLoop, this);

    gameLoop();
    // gameLoop();
}

RType::Server::RTypeServer::~RTypeServer()
{
}

void RType::Server::RTypeServer::gameLoop()
{
    while (!_IOContext.stopped()) {

        _IOContext.run_one();
    }
}
