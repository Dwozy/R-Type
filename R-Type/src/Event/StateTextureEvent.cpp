/*
** EPITECH PROJECT, 2023
** StateTextureEvent.cpp
** File description:
** StateTextureEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::setTextureState(struct RType::Protocol::StatePlayerData stateData)
    {
        if (_searchEntity(stateData.id)) {
            std::size_t id = _findEntity(stateData.id);
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
            auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent> () [entity];
            if (!texture)
                return;
            std::cout << "Invincibility is " << static_cast<std::size_t> (stateData.invincibility) << std::endl;
            texture.value().animated = (stateData.invincibility == static_cast<uint8_t> (true)) ? true : false;
            if (!texture.value().animated) {
                texture.value().animeid = 0;
                texture.value().sprite.setTextureRect(texture.value().textureRects[texture.value().animeid]);
            }
        }
    }

    void RTypeClient::setTextureStateCallback()
    {
        auto &refHandleTransform = _gameEngine.eventManager.addHandler<struct RType::Protocol::StatePlayerData>(
            static_cast<GameEngine::EventType>(GameEngine::Event::GetStateTexture));
        auto handleGetTransform =
            std::bind(&RType::Client::RTypeClient::setTextureState, this, std::placeholders::_1);
        refHandleTransform.subscribe(handleGetTransform);
    }
} // namespace RType::Client
