/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Movement
*/

#include "RTypeClient.hpp"
#include <iostream>

namespace RType::Client
{
    void RTypeClient::updatePlayerMovement(const GameEngine::TransformComponent &transform)
    {
        std::vector<std::byte> data = Serialization::serializeData<RType::Protocol::MoveData>(
            {_id, transform.position.x, transform.position.y, transform.velocity.x, transform.velocity.y});

        _udpClient.sendDataInformation(data, static_cast<uint8_t>(rtype::PacketType::MOVE));
    }

    void RTypeClient::handlePlayerMovement()
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
        GameEngine::Vector2<float> direction(0, 0);

        if (!transforms[_id].has_value())
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

    void RTypeClient::handleOtherPlayerMovement(struct rtype::Event event)
    {
        auto entity = std::any_cast<RType::Protocol::MoveData>(event.data);
        _gameEngine.eventManager.getHandler<RType::Protocol::MoveData>(GameEngine::Event::DeleteEntity).publish(entity);
    }

    void RTypeClient::updateOtherPlayerMovement(RType::Protocol::MoveData entity)
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        std::cerr << "entity: " << entity.id << " before if" << std::endl;
        if (!transforms[entity.id].has_value() && entity.id == _id)
            return;
        std::cerr << "entity: " << entity.id << " after if" << std::endl;
        transforms[entity.id]->position = {entity.x, entity.y};
        transforms[entity.id]->velocity = {entity.dx, entity.dy};
    }
} // namespace RType::Client
