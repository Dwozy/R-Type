/*
** EPITECH PROJECT, 2023
** HandleEvent.cpp
** File description:
** HandleEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::handleDisconnexion(struct RType::Event event)
    {
        struct RType::Protocol::EntityIdData entity = std::any_cast<struct RType::Protocol::EntityIdData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::EntityIdData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::DeleteEntity))
            .publish(entity);
    }

    void RTypeClient::handleTransformComponent(struct RType::Event event)
    {
        struct RType::Protocol::TransformData transformData =
            std::any_cast<struct RType::Protocol::TransformData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::TransformData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::GetTransform))
            .publish(transformData);
    }

    void RTypeClient::handleTextureComponent(struct RType::Event event)
    {
        struct RType::Protocol::TextureData textureData =
            std::any_cast<struct RType::Protocol::TextureData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::TextureData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::GetTexture))
            .publish(textureData);
    }

    void RTypeClient::handleCollisionComponent(struct RType::Event event)
    {
        struct RType::Protocol::CollisionData collisionData =
            std::any_cast<struct RType::Protocol::CollisionData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::CollisionData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::GetCollision))
            .publish(collisionData);
    }

    void RTypeClient::handleControllableComponent(struct RType::Event event)
    {
        struct RType::Protocol::ControllableData collisionData =
            std::any_cast<struct RType::Protocol::ControllableData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::ControllableData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::GetControllable))
            .publish(collisionData);
    }

    void RTypeClient::handleTextureState(struct RType::Event event)
    {
        struct RType::Protocol::StatePlayerData stateData =
            std::any_cast<struct RType::Protocol::StatePlayerData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::StatePlayerData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::GetStateTexture))
            .publish(stateData);
    }

    void RTypeClient::handleScore(struct RType::Event event)
    {
        struct RType::Protocol::ScoreData stateData = std::any_cast<struct RType::Protocol::ScoreData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::ScoreData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::GetScore))
            .publish(stateData);
    }

    void RTypeClient::handleEndGame(struct RType::Event event)
    {
        struct RType::Protocol::EndGameData endGameData =
            std::any_cast<struct RType::Protocol::EndGameData>(event.data);
        _gameEngine.eventManager
            .getHandler<struct RType::Protocol::EndGameData>(
                static_cast<GameEngine::EventType>(GameEngine::Event::GetEndGame))
            .publish(endGameData);
    }

    void RTypeClient::handleEvent()
    {
        struct RType::Event event;

        while (_eventQueue.size() != 0) {
            event = _eventQueue.pop();
            switch (event.packetType) {
            case static_cast<uint8_t>(RType::Protocol::ComponentType::TRANSFORM):
                handleTransformComponent(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE):
                handleTextureComponent(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::ComponentType::COLLISION):
                handleCollisionComponent(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::ComponentType::CONTROLLABLE):
                handleControllableComponent(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::PacketType::DESTROY):
                handleDisconnexion(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_STATE):
                handleTextureState(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::PacketType::SCORE):
                handleScore(event);
                break;
            case static_cast<uint8_t>(RType::Protocol::PacketType::ENDGAME):
                handleEndGame(event);
                break;
            }
        }
    }
} // namespace RType::Client
