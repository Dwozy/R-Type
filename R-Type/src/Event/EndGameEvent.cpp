/*
** EPITECH PROJECT, 2023
** EndGameData.cpp
** File description:
** EndGameData
*/

#include "RTypeClient.hpp"

namespace RType::Client
{
    void RTypeClient::setEndGameState(struct RType::Protocol::EndGameData endGameData)
    {
        if (endGameData.endGameState == static_cast<uint8_t>(RType::GameState::WIN))
            _gameState = RType::GameState::WIN;
        if (endGameData.endGameState == static_cast<uint8_t>(RType::GameState::LOSE))
            _gameState = RType::GameState::LOSE;
    }

    void RTypeClient::setEndGameCallback()
    {
        auto &refHandlerEndGame = _gameEngine.eventManager.addHandler<struct RType::Protocol::EndGameData>(
            static_cast<GameEngine::EventType>(GameEngine::Event::GetEndGame));
        auto handleEndGame = std::bind(&RType::Client::RTypeClient::setEndGameState, this, std::placeholders::_1);
        refHandlerEndGame.subscribe(handleEndGame);
    }
} // namespace RType::Client
