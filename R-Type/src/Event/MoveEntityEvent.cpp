// /*
// ** EPITECH PROJECT, 2023
// ** MoveEntityEvent.cpp
// ** File description:
// ** MoveEntityEvent
// */

// #include "RTypeClient.hpp"

// namespace RType::Client
// {
//     void RTypeClient::updatePlayerMovement(const GameEngine::TransformComponent &transform)
//     {
//         std::vector<std::byte> data = Serialization::serializeData<RType::Protocol::MoveData>(
//             {_serverId, transform.position.x, transform.position.y, transform.velocity.x, transform.velocity.y},
//             sizeof(RType::Protocol::MoveData));

//         std::cout << transform.velocity.x << std::endl;
//         std::cout << transform.velocity.y << std::endl;
//         _udpClient.sendDataInformation(data, static_cast<uint8_t>(RType::PacketType::MOVE));
//     }

//     void RTypeClient::handlePlayerMovement()
//     {
//         auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
//         GameEngine::Vector2<float> direction(0, 0);

//         if (!transforms[_id].has_value())
//             return;
//         auto &controllables = _gameEngine.registry.getComponent<GameEngine::ControllableComponent>();
//         if (!controllables[_id])
//             return;
//         if (GameEngine::InputManager::isKeyPressed(controllables[_id].value().key_up))
//             direction.x += 1;
//         if (GameEngine::InputManager::isKeyPressed(controllables[_id].value().key_down))
//             direction.x -= 1;
//         if (GameEngine::InputManager::isKeyPressed(controllables[_id].value().key_left))
//             direction.y -= 1;
//         if (GameEngine::InputManager::isKeyPressed(controllables[_id].value().key_right))
//             direction.y += 1;
//         direction = direction.normalize();
//         if (direction != transforms[_id]->velocity.normalize())
//             _gameEngine.eventManager
//                 .getHandler<GameEngine::TransformComponent>(
//                     static_cast<GameEngine::EventType>(GameEngine::Event::PlayerMoveEvent))
//                 .publish(transforms[_id].value());
//     }

//     void RTypeClient::setMovementEntityCallback()
//     {
//         auto &refHandlerMove = _gameEngine.eventManager.addHandler<GameEngine::TransformComponent>(
//             static_cast<GameEngine::EventType>(GameEngine::Event::PlayerMoveEvent));
//         auto handleUpdateMove =
//             std::bind(&RType::Client::RTypeClient::updatePlayerMovement, this, std::placeholders::_1);
//         refHandlerMove.subscribe(handleUpdateMove);
//     }
// } // namespace RType::Client
