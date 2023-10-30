/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ShootEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::getTextureInformation(struct RType::Protocol::TextureData textureData)
    {
        auto &textures = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();
        std::size_t id = 0;

        if (!_searchEntity(textureData.id)) {
            GameEngine::Entity entity = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                entity, GameEngine::NetworkIdComponent{textureData.id});
            GameEngine::TextureComponent texture = {_listPathTextureId.at(textureData.idTexture), GameEngine::Sprite(),
                false, {}, 0, true, 0, 0, textureData.renderLayer};
            auto &entityTexture = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(entity, texture);
        }
        id = _findEntity(textureData.id);
        if (!textures[id]) {
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
            std::vector<GameEngine::Rect<int>> rectTextures;
            rectTextures.push_back({static_cast<int>(textureData.rectLeft), static_cast<int>(textureData.rectTop),
                static_cast<int>(textureData.rectWidth), static_cast<int>(textureData.rectHeight)});
            GameEngine::TextureComponent texture = {_listPathTextureId.at(textureData.idTexture), GameEngine::Sprite(),
                false, rectTextures, 0, true, 0, 0, textureData.renderLayer};
            auto &entityTexture = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(entity, texture);
        } else {
            GameEngine::Recti rect = {
                textureData.rectLeft, textureData.rectHeight, textureData.rectWidth, textureData.rectHeight};

            try {
                textures[id].value().textureRects.at(textureData.idOrderTexture);
                struct RType::Protocol::TextureResponse response = {
                    .id = textureData.id, .idTexture = textureData.idOrderTexture};
                std::vector<std::byte> dataToSend =
                    Serialization::serializeData<struct RType::Protocol::TextureResponse>(response, sizeof(response));
                _udpClient.sendDataInformation(
                    dataToSend, static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_RES));
            } catch (const std::out_of_range &) {
                textures[id].value().textureRects.resize(textureData.idOrderTexture + 1);
                textures[id].value().textureRects[textureData.idOrderTexture] = rect;
            }
            // textures[id].value().textureRects.at()
            // BESOIN D'ENVOYER MESSAGE AU SERVEUR POUR DIRE I GOT IT
        }
    }

    void RTypeClient::setTextureCallback()
    {
        auto &refHandleTexture =
            _gameEngine.eventManager.addHandler<struct RType::Protocol::TextureData>(GameEngine::Event::GetTexture);
        auto handleGetTexture =
            std::bind(&RType::Client::RTypeClient::getTextureInformation, this, std::placeholders::_1);
        refHandleTexture.subscribe(handleGetTexture);
    }
} // namespace RType::Client
