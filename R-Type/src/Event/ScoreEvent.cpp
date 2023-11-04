/*
** EPITECH PROJECT, 2023
** ScoreEvent.cpp
** File description:
** ScoreEvent
*/

#include "RTypeClient.hpp"
#include "components/FontComponent.hpp"
#include "components/TextComponent.hpp"
#include "utils/SfmlTypes.hpp"
#include "Protocol.hpp"

namespace RType::Client
{
    void RTypeClient::setScore(struct RType::Protocol::ScoreData scoreData)
    {
        auto &text = _gameEngine.registry.getComponent<GameEngine::TextComponent> () [_scoreTextEntity];
        if (!text)
            return;
        _points = static_cast<std::size_t> (scoreData.score);
        text.value().text.setString(std::to_string(_points));
    }

    void RTypeClient::setScoreCallback()
    {
        auto &refHandlerScore = _gameEngine.eventManager.addHandler<struct RType::Protocol::ScoreData>(
            static_cast<GameEngine::EventType>(GameEngine::Event::GetScore));
        auto handleScore = std::bind(&RType::Client::RTypeClient::setScore, this, std::placeholders::_1);
        refHandlerScore.subscribe(handleScore);
    }
} // namespace RType::Client
