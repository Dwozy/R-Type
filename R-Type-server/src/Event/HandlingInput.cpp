/*
** EPITECH PROJECT, 2023
** HandlingInput.cpp
** File description:
** HandlingInput
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::handleInput(struct RType::Event event)
    {
        auto inputInfo = std::any_cast<RType::Protocol::InputData>(event.data);
        std::size_t id = 0;

        if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::SHOOT)) {
            auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
            std::size_t index = static_cast<std::size_t>(inputInfo.id);
            if (!transforms[inputInfo.id])
                return;
            struct RType::Protocol::ShootData shootInfo = {
                .id = inputInfo.id,
                .x = transforms[inputInfo.id].value().position.x,
                .y = transforms[inputInfo.id].value().position.y,
                .dx = transforms[inputInfo.id].value().velocity.x,
                .dy = transforms[inputInfo.id].value().velocity.y,
            };
            handleShoot(shootInfo);
        }
        if (inputInfo.state == static_cast<uint8_t>(false)) {
            auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
            if (!transforms[inputInfo.id])
                return;
            struct RType::Protocol::MoveData moveInfo = {
                .id = inputInfo.id,
                .x = transforms[inputInfo.id].value().position.x,
                .y = transforms[inputInfo.id].value().position.y,
                .dx = 0.0,
                .dy = 0.0,
            };
            handleMove(moveInfo);
        } else {
            if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::UP)) {
                auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
                if (!transforms[inputInfo.id])
                    return;
                struct RType::Protocol::MoveData moveInfo = {
                    .id = inputInfo.id,
                    .x = transforms[inputInfo.id].value().position.x,
                    .y = transforms[inputInfo.id].value().position.y,
                    .dx = transforms[inputInfo.id].value().velocity.x,
                    .dy = -1.0 * RType::PLAYER_SPEED,
                };
                handleMove(moveInfo);
            }
            if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::DOWN)) {
                auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
                if (!transforms[inputInfo.id])
                    return;
                struct RType::Protocol::MoveData moveInfo = {
                    .id = inputInfo.id,
                    .x = transforms[inputInfo.id].value().position.x,
                    .y = transforms[inputInfo.id].value().position.y,
                    .dx = transforms[inputInfo.id].value().velocity.x,
                    .dy = 1.0 * RType::PLAYER_SPEED,
                };
                handleMove(moveInfo);
            }
            if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::LEFT)) {
                auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
                if (!transforms[inputInfo.id])
                    return;
                struct RType::Protocol::MoveData moveInfo = {
                    .id = inputInfo.id,
                    .x = transforms[inputInfo.id].value().position.x,
                    .y = transforms[inputInfo.id].value().position.y,
                    .dx = -1.0 * RType::PLAYER_SPEED,
                    .dy = transforms[inputInfo.id].value().velocity.y,
                };
                std::cout << "LEEEEFFTT" << std::endl;
                handleMove(moveInfo);
            }
            if (inputInfo.inputId == static_cast<uint8_t>(RType::Protocol::InputType::RIGHT)) {
                auto transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
                if (!transforms[inputInfo.id])
                    return;
                struct RType::Protocol::MoveData moveInfo = {
                    .id = inputInfo.id,
                    .x = transforms[inputInfo.id].value().position.x,
                    .y = transforms[inputInfo.id].value().position.y,
                    .dx = 1.0 * RType::PLAYER_SPEED,
                    .dy = transforms[inputInfo.id].value().velocity.y,
                };
                std::cout << "RIGHHTT" << std::endl;
                handleMove(moveInfo);
            }
        }
    }
} // namespace RType::Server
