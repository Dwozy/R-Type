/*
** EPITECH PROJECT, 2023
** EntityUtils.cpp
** File description:
** EntityUtils
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    std::size_t RTypeClient::findEntity(const std::size_t &networkId)
    {
        const auto &ids = _gameEngine.registry.getComponent<GameEngine::NetworkIdComponent>();

        for (std::size_t i = 0; i < ids.size(); i++) {
            const auto &id = ids[i];

            if (id && id.value().id == networkId)
                return i;
        }
        throw Error::InvalidEntityIdError();
    }

    bool RTypeClient::searchEntity(const std::size_t &networkId)
    {
        const auto &ids = _gameEngine.registry.getComponent<GameEngine::NetworkIdComponent>();

        for (std::size_t i = 0; i < ids.size(); i++) {
            const auto &id = ids[i];

            if (id && id.value().id == networkId)
                return true;
        }
        return false;
    }

} // namespace RType::Client
