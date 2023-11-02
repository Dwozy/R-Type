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
            std::vector<GameEngine::Rect<int>> rectTextures;
            rectTextures.push_back({static_cast<int>(textureData.rectLeft), static_cast<int>(textureData.rectTop),
                static_cast<int>(textureData.rectWidth), static_cast<int>(textureData.rectHeight)});
            if (_listPathTextureId.find(textureData.idTexture) != _listPathTextureId.end() &&
                textureData.idTexture != static_cast<uint8_t>(RType::TextureType::NONE)) {
                GameEngine::Rect<int> textureSize = {static_cast<int>(textureData.rectTextureLeft),
                    static_cast<int>(textureData.rectTextureTop), static_cast<int>(textureData.rectTextureWidth),
                    static_cast<int>(textureData.rectTextureHeight)};

                GameEngine::TextureComponent texture = {.path = _listPathTextureId.at(textureData.idTexture),
                    .sprite = GameEngine::Sprite(),
                    .animated = (textureData.isAnimated == '1') ? true : false,
                    .textureSize = textureSize,
                    .textureRects = rectTextures,
                    .animationSpeed = textureData.animationSpeed,
                    .isRendered = true,
                    .lastUpdate = 0,
                    .animeid = 0,
                    .renderLayer = textureData.renderLayer};

                auto &entityTexture = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(entity, texture);
                _gameEngine.assetManager.loadTexture(_listPathTextureId.at(textureData.idTexture), textureSize);
                entityTexture.value().sprite.load(
                    _gameEngine.assetManager.getTexture(_listPathTextureId.at(textureData.idTexture)));
                entityTexture.value().sprite.setTextureRect(
                    entityTexture.value().textureRects[entityTexture.value().animeid]);
            }
        }
        id = _findEntity(textureData.id);
        if (!textures[id]) {
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
            std::vector<GameEngine::Rect<int>> rectTextures;
            rectTextures.push_back({static_cast<int>(textureData.rectLeft), static_cast<int>(textureData.rectTop),
                static_cast<int>(textureData.rectWidth), static_cast<int>(textureData.rectHeight)});
            if (_listPathTextureId.find(textureData.idTexture) != _listPathTextureId.end() &&
                textureData.idTexture != static_cast<uint8_t>(RType::TextureType::NONE)) {
                GameEngine::Rect<int> textureSize = {static_cast<int>(textureData.rectTextureLeft),
                    static_cast<int>(textureData.rectTextureTop), static_cast<int>(textureData.rectTextureWidth),
                    static_cast<int>(textureData.rectTextureHeight)};

                GameEngine::TextureComponent texture = {.path = _listPathTextureId.at(textureData.idTexture),
                    .sprite = GameEngine::Sprite(),
                    .animated = (textureData.isAnimated == '1') ? true : false,
                    .textureSize = textureSize,
                    .textureRects = rectTextures,
                    .animationSpeed = textureData.animationSpeed,
                    .isRendered = true,
                    .lastUpdate = 0,
                    .animeid = 0,
                    .renderLayer = textureData.renderLayer};
                auto &entityTexture = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(entity, texture);

                _gameEngine.assetManager.loadTexture(_listPathTextureId.at(textureData.idTexture), textureSize);
                entityTexture.value().sprite.load(
                    _gameEngine.assetManager.getTexture(_listPathTextureId.at(textureData.idTexture)));
                entityTexture.value().sprite.setTextureRect(
                    entityTexture.value().textureRects[entityTexture.value().animeid]);
            }
        } else {
            GameEngine::Recti rect = {static_cast<int>(textureData.rectLeft), static_cast<int>(textureData.rectTop),
                static_cast<int>(textureData.rectWidth), static_cast<int>(textureData.rectHeight)};

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
        }
    }

    void RTypeClient::setTextureCallback()
    {
        auto &refHandleTexture =
            _gameEngine.eventManager.addHandler<struct RType::Protocol::TextureData>(static_cast<GameEngine::EventType> (GameEngine::Event::GetTexture));
        auto handleGetTexture =
            std::bind(&RType::Client::RTypeClient::getTextureInformation, this, std::placeholders::_1);
        refHandleTexture.subscribe(handleGetTexture);
    }
} // namespace RType::Client
