// /*
// ** EPITECH PROJECT, 2023
// ** R-Type
// ** File description:
// ** ShootEvent
// */

// #include "RTypeClient.hpp"

// namespace RType::Client
// {
//     void RTypeClient::shootEvent(const GameEngine::TransformComponent &transform)
//     {
//         std::vector<std::byte> data = Serialization::serializeData<struct RType::Shoot>(
//             {static_cast<uint16_t>(_serverId), transform.position.x, transform.position.y}, sizeof(struct RType::Shoot));

//         _udpClient.sendDataInformation(data, static_cast<uint8_t>(RType::PacketType::SHOOT));
//     }

//     void RTypeClient::handlePlayerShoot()
//     {
//         static bool shotable = true;
//         if (!_isAlive)
//             return;
//         auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
//         if (!transforms[_id].has_value())
//             return;

//         if (GameEngine::InputManager::isKeyPressed(GameEngine::Input::Keyboard::Space) == true && shotable == true) {
//             _gameEngine.eventManager.getHandler<GameEngine::TransformComponent>(static_cast<GameEngine::EventType> (GameEngine::Event::PlayerShootEvent))
//                 .publish(transforms[_id].value());
//             shotable = false;
//         }
//         if (GameEngine::InputManager::isKeyReleased(GameEngine::Input::Keyboard::Space) == true)
//             shotable = true;
//     }

//     void RTypeClient::setShootCallback()
//     {
//         auto &refHandlerShoot =
//             _gameEngine.eventManager.addHandler<GameEngine::TransformComponent>(static_cast<GameEngine::EventType> (GameEngine::Event::PlayerShootEvent));
//         auto handleShootEvent = std::bind(&RType::Client::RTypeClient::shootEvent, this, std::placeholders::_1);
//         refHandlerShoot.subscribe(handleShootEvent);
//     }
// } // namespace RType::Client
