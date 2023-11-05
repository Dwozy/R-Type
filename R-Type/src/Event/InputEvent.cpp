/*
** EPITECH PROJECT, 2023
** InputEvent.cpp
** File description:
** InputEvent
*/

#include "RTypeClient.hpp"
#include "Event.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::handleInput(struct GameEngine::Input::InputInfo input)
    {
        static bool _shoot = true;
        auto &networkId = _gameEngine.registry.getComponent<GameEngine::NetworkIdComponent>();
        if (!networkId[input.id])
            return;
        size_t id = networkId[input.id].value().id;
        struct RType::Protocol::InputData inputData = {.id = static_cast<uint16_t>(id),
            .inputId = static_cast<uint8_t>(input.idInput),
            .state = static_cast<uint8_t>(input.state)};
        std::vector<std::byte> data =
            Serialization::serializeData<RType::Protocol::InputData>(inputData, sizeof(inputData));

        _udpClient.sendDataInformation(data, static_cast<uint8_t>(RType::Protocol::ComponentType::INPUT));
    }

    void RTypeClient::setInputCallback()
    {
        auto &refHandlerInput = _gameEngine.eventManager.addHandler<struct GameEngine::Input::InputInfo>(
            static_cast<GameEngine::EventType>(GameEngine::Event::SendInput));
        auto handleInput = std::bind(&RType::Client::RTypeClient::handleInput, this, std::placeholders::_1);
        refHandlerInput.subscribe(handleInput);
    }
} // namespace RType::Client
