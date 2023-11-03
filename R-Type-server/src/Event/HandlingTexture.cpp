/*
** EPITECH PROJECT, 2023
** HandlingTexture.cpp
** File description:
** HandlingTexture
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RTypeServer::handleTextureResponse(struct RType::Event event)
    {
        struct RType::Protocol::TextureResponse response =
            std::any_cast<struct RType::Protocol::TextureResponse>(event.data);

        if (_listInfosComponent.find(response.id) != _listInfosComponent.end()) {
            try {
                _listInfosComponent[event.port]
                    .at(response.id)
                    .at(RType::Protocol::ComponentType::TEXTURE)[response.idTexture] = false;
            } catch (const std::out_of_range &) {
                return;
            }
        }
    }

    void RTypeServer::sendTextureComponent(
        uint16_t id, std::size_t index, GameEngine::TextureComponent texture, asio::ip::udp::endpoint &endpoint)
    {
        struct RType::Protocol::TextureData textureData = {.id = id,
            .idTexture = static_cast<uint8_t>(_listIdType.at(id)),
            .idOrderTexture = static_cast<uint8_t>(index),
            .rectLeft = static_cast<uint16_t>(texture.textureRects[index].left),
            .rectTop = static_cast<uint16_t>(texture.textureRects[index].top),
            .rectWidth = static_cast<uint16_t>(texture.textureRects[index].width),
            .rectHeight = static_cast<uint16_t>(texture.textureRects[index].height),
            .rectTextureLeft = static_cast<uint16_t>(texture.textureSize.left),
            .rectTextureTop = static_cast<uint16_t>(texture.textureSize.top),
            .rectTextureWidth = static_cast<uint16_t>(texture.textureSize.width),
            .rectTextureHeight = static_cast<uint16_t>(texture.textureSize.height),
            .renderLayer = static_cast<uint8_t>(texture.renderLayer),
            .isAnimated = (texture.animated) ? static_cast<uint8_t>('1') : static_cast<uint8_t>('0'),
            .animationSpeed = texture.animationSpeed};
        std::vector<std::byte> dataToSend =
            Serialization::serializeData<struct RType::Protocol::TextureData>(textureData, sizeof(textureData));
        _udpServer.sendInformation(static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE), dataToSend, endpoint);
    }

    void RTypeServer::checkSendingTexture(
        std::vector<bool> listDisplayTexture, const GameEngine::Entity &entity, asio::ip::udp::endpoint &endpoint)
    {
        auto texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entity];

        for (std::size_t index = 0; index < listDisplayTexture.size(); index++) {
            if (listDisplayTexture[index])
                sendTextureComponent(static_cast<uint16_t>(entity), index, texture.value(), endpoint);
        }
    }

    void RTypeServer::broadcastTextureComponent()
    {
        auto &textures = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();

        for (std::size_t i = 0; i < textures.size(); i++) {
            auto texture = textures[i];
            if (!texture)
                continue;
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(i);
            for (auto client : _udpServer.getListClients()) {
                if (_listInfosComponent[client.first].find(i) != _listInfosComponent[client.first].end()) {
                    checkSendingTexture(
                        _listInfosComponent[client.first].at(i).at(RType::Protocol::ComponentType::TEXTURE), entity,
                        client.second);
                }
            }
        }
    }
} // namespace RType::Server
