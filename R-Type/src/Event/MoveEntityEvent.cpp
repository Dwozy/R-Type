/*
** EPITECH PROJECT, 2023
** MoveEntityEvent.cpp
** File description:
** MoveEntityEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::updatePlayerMovement(const GameEngine::TransformComponent &transform)
    {
        std::vector<std::byte> data = Serialization::serializeData<RType::Protocol::MoveData>(
            {_serverId, transform.position.x, transform.position.y, transform.velocity.x, transform.velocity.y},
            sizeof(RType::Protocol::MoveData));

        _udpClient.sendDataInformation(data, static_cast<uint8_t>(rtype::PacketType::MOVE));
    }

    void RTypeClient::handlePlayerMovement()
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
        GameEngine::Vector2<float> direction(0, 0);

        if (!transforms[_id])
            return;
        std::cout << "x: " << transforms[_id]->position.x << " y: " << transforms[_id]->position.y << std::endl;
        if (GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Z) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Up))
            direction.x += 1;
        if (GameEngine::isKeyPressed(GameEngine::Input::Keyboard::S) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Down))
            direction.x -= 1;
        if (GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Q) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Left))
            direction.y -= 1;
        if (GameEngine::isKeyPressed(GameEngine::Input::Keyboard::D) ||
            GameEngine::isKeyPressed(GameEngine::Input::Keyboard::Right))
            direction.y += 1;
        direction = direction.normalize();
        if (direction != transforms[_id]->velocity.normalize())
            _gameEngine.eventManager.getHandler<GameEngine::TransformComponent>(GameEngine::Event::PlayerMoveEvent)
                .publish(transforms[_id].value());
    }

    void RTypeClient::setMovementEntityCallback()
    {
        auto &refHandlerMove =
            _gameEngine.eventManager.addHandler<GameEngine::TransformComponent>(GameEngine::Event::PlayerMoveEvent);
        auto handleUpdateMove =
            std::bind(&RType::Client::RTypeClient::updatePlayerMovement, this, std::placeholders::_1);
        refHandlerMove.subscribe(handleUpdateMove);
    }
} // namespace RType::Client
