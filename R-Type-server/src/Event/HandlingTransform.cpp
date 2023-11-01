/*
** EPITECH PROJECT, 2023
** HandlingTransform.cpp
** File description:
** HandlingTransform
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::sendTransformComponent(uint16_t id, GameEngine::Vector2<float> position,
        GameEngine::Vector2<float> velocity, asio::ip::udp::endpoint &endpoint)
    {
        struct RType::Protocol::TransformData transformData = {
            .id = id,
            .x = position.x,
            .y = position.y,
            .dx = velocity.x,
            .dy = velocity.y,
        };
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::TransformData>(transformData, sizeof(transformData));
        _udpServer.sendInformation(
            static_cast<uint8_t>(RType::Protocol::ComponentType::TRANSFORM), dataToSend, endpoint);
    }

    void RTypeServer::broadcastTransformComponent()
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        for (std::size_t i = 0; i < transforms.size(); i++) {
            auto transform = transforms[i];
            if (!transform)
                continue;
            for (auto client : _udpServer.getListClients()) {
                if (_listInfosComponent[client.first].find(i) != _listInfosComponent[client.first].end()) {
                    sendTransformComponent(
                        static_cast<uint16_t>(i), transform.value().position, transform.value().velocity, client.second);
                }
            }
        }
    }
} // namespace RType::Server
