/*
** EPITECH PROJECT, 2023
** ControllableEvent.cpp
** File description:
** ControllableEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::setControllable(struct RType::Protocol::ControllableData controllableData)
    {
        // std::cout << "Controllable " << controllableData.id << std::endl;
        GameEngine::ControllableComponent con = {GameEngine::Input::Keyboard::Z, GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S, GameEngine::Input::Keyboard::D, 100.0f};

        if (_searchEntity(controllableData.id)) {
            std::size_t id = _findEntity(controllableData.id);
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
            _gameEngine.registry.addComponent<GameEngine::ControllableComponent>(entity, con);
            std::cout << "Set Controllable on " << id << std::endl;
            _id = entity;
            _serverId = id;
        }
    }

    void RTypeClient::setControllableCallback()
    {
        auto &refHandlerNew =
            _gameEngine.eventManager.addHandler<struct RType::Protocol::ControllableData>(GameEngine::Event::GetControllable);
        auto handleNew = std::bind(&RType::Client::RTypeClient::setControllable, this, std::placeholders::_1);
        refHandlerNew.subscribe(handleNew);
    }
} // namespace RType::Client
