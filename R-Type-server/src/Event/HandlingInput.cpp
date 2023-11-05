/*
** EPITECH PROJECT, 2023
** HandlingInput.cpp
** File description:
** HandlingInput
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    GameEngine::Vector2<float> RTypeServer::handlingMovement(
        GameEngine::TransformComponent &transform, struct RType::Protocol::InputData inputInfo)
    {
        if (inputInfo.state == static_cast<uint8_t>(false))
            return {0, 0};
        if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::RIGHT))
            return {1.0 * RType::PLAYER_SPEED, transform.velocity.y};
        if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::LEFT))
            return {-1.0 * RType::PLAYER_SPEED, transform.velocity.y};
        if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::DOWN))
            return {transform.velocity.x, 1.0 * RType::PLAYER_SPEED};
        if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::UP))
            return {transform.velocity.x, -1.0 * RType::PLAYER_SPEED};
        return transform.velocity;
    }

    void RTypeServer::handleInput(struct RType::Event event)
    {
        struct RType::Protocol::InputData inputInfo = std::any_cast<RType::Protocol::InputData>(event.data);

        if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::SHOOT)) {
            auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
            if (!transforms[inputInfo.id])
                return;
            if (_chargedAttackTimer.find(inputInfo.id) != _chargedAttackTimer.end() &&
                inputInfo.state == static_cast<uint8_t>(true) && _chargedAttackTimer.at(inputInfo.id).first) {
                _chargedAttackTimer.at(inputInfo.id).second = std::chrono::steady_clock::now();
                _chargedAttackTimer.at(inputInfo.id).first = false;
            } else if (inputInfo.state == static_cast<uint8_t>(false) &&
                       _chargedAttackTimer.find(inputInfo.id) != _chargedAttackTimer.end()) {
                struct RType::Protocol::ShootData shootInfo = {
                    .id = inputInfo.id,
                    .x = transforms[inputInfo.id].value().position.x,
                    .y = transforms[inputInfo.id].value().position.y,
                    .dx = transforms[inputInfo.id].value().velocity.x,
                    .dy = transforms[inputInfo.id].value().velocity.y,
                };
                handleShoot(shootInfo);
                _chargedAttackTimer.at(inputInfo.id).first = true;
            }
        } else {
            auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
            if (!transforms[inputInfo.id])
                return;
            struct RType::Protocol::MoveData moveInfo = {
                .id = inputInfo.id,
                .x = transforms[inputInfo.id].value().position.x,
                .y = transforms[inputInfo.id].value().position.y,
                .dx = handlingMovement(transforms[inputInfo.id].value(), inputInfo).x,
                .dy = handlingMovement(transforms[inputInfo.id].value(), inputInfo).y,
            };
            handleMove(moveInfo);
        }
    }
} // namespace RType::Server
