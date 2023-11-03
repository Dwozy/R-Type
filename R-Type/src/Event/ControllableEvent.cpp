/*
** EPITECH PROJECT, 2023
** ControllableEvent.cpp
** File description:
** ControllableEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"
#include "components/InputComponent.hpp"

namespace RType::Client
{
    void RTypeClient::setControllable(struct RType::Protocol::ControllableData controllableData)
    {
        if (_searchEntity(controllableData.id)) {
            std::size_t id = _findEntity(controllableData.id);
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
            auto &input = _gameEngine.registry.addComponent<GameEngine::InputComponent>(entity, {});

            input.value().addInput(GameEngine::Input::InputType::SHOOT, GameEngine::Input::Keyboard::Space);
            input.value().addInput(GameEngine::Input::InputType::UP, GameEngine::Input::Keyboard::Z);
            input.value().addInput(GameEngine::Input::InputType::LEFT, GameEngine::Input::Keyboard::Q);
            input.value().addInput(GameEngine::Input::InputType::DOWN, GameEngine::Input::Keyboard::S);
            input.value().addInput(GameEngine::Input::InputType::RIGHT, GameEngine::Input::Keyboard::D);
            _id = entity;
            _serverId = controllableData.id;
        }
    }

    void RTypeClient::setControllableCallback()
    {
        auto &refHandlerNew = _gameEngine.eventManager.addHandler<struct RType::Protocol::ControllableData>(
            static_cast<GameEngine::EventType>(GameEngine::Event::GetControllable));
        auto handleNew = std::bind(&RType::Client::RTypeClient::setControllable, this, std::placeholders::_1);
        refHandlerNew.subscribe(handleNew);
    }
} // namespace RType::Client
