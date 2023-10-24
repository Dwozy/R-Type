/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ShootEvent
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::shootEvent(const GameEngine::TransformComponent &transform)
    {
        std::vector<std::byte> data = Serialization::serializeData<struct rtype::Shoot>(
            {static_cast<uint16_t> (_id), transform.position.x, transform.position.y}, sizeof(struct rtype::Shoot));

        _udpClient.sendDataInformation(data, static_cast<uint8_t>(rtype::PacketType::SHOOT));
    }

    void RTypeClient::handlePlayerShoot()
    {
        static bool shotable = true;
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
        if (!transforms[_id].has_value())
            return;
        if (GameEngine::InputManager::isKeyPressed(GameEngine::Input::Keyboard::Space) == true && shotable == true) {
            _gameEngine.eventManager.getHandler<GameEngine::TransformComponent>(GameEngine::Event::PlayerShootEvent)
                    .publish(transforms[_id].value());
            shotable = false;
        }
        if (GameEngine::InputManager::isKeyReleased(GameEngine::Input::Keyboard::Space) == true)
            shotable = true;
    }

    void RTypeClient::setShootCallback()
    {
        auto &refHandlerShoot =
            _gameEngine.eventManager.addHandler<GameEngine::TransformComponent>(GameEngine::Event::PlayerShootEvent);
        auto handleShootEvent =
            std::bind(&RType::Client::RTypeClient::shootEvent, this, std::placeholders::_1);
        refHandlerShoot.subscribe(handleShootEvent);
    }
} // namespace RType::Client

