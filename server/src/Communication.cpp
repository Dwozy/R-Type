/*
** EPITECH PROJECT, 2023
** Communication.cpp
** File description:
** Communication
*/

#include "Communication.hpp"

void Network::Communication::sendInformation(void *data, std::size_t size, asio::ip::udp::socket &socket,
    asio::ip::udp::endpoint &clientEndpoint, struct rtype::HeaderDataPacket header)
{
    socket.async_send_to(asio::buffer(&header, sizeof(header)), clientEndpoint,
        [&](const asio::error_code &error, std::size_t sendBytes) {
            if (!error) {
                std::cout << "Send : " << sendBytes << " bytes as header." << std::endl;
            }
        });
    socket.async_send_to(
        asio::buffer(data, size), clientEndpoint, [&](const asio::error_code &error, std::size_t sendBytes) {
            if (!error)
                std::cout << "Send : " << sendBytes << " bytes as data." << std::endl;
        });
}

void Network::Communication::sendInformation(void *data, std::size_t size, asio::ip::tcp::socket &socket,
    asio::ip::tcp::endpoint &, struct rtype::HeaderDataPacket header)
{
    asio::async_write(
        socket, asio::buffer(&header, sizeof(header)), [&](const asio::error_code &error, std::size_t sendBytes) {
            if (!error) {
                std::cout << "Send : " << sendBytes << " bytes as header." << std::endl;
            }
        });
    asio::async_write(socket, asio::buffer(data, size), [&](const asio::error_code &error, std::size_t sendBytes) {
        if (!error)
            std::cout << "Send : " << sendBytes << " bytes as data." << std::endl;
    });
}
