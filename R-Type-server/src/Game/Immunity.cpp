/*
** EPITECH PROJECT, 2023
** Immunity.cpp
** File description:
** Immunity
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RType::Server::RTypeServer::handleImmunity(std::chrono::steady_clock::time_point &now)
    {
        for (auto &playerTimer : _timerLifePoint) {
            if (playerTimer.second.first)
                continue;
            std::chrono::duration<float> _deltaTimerInvicibility =
                std::chrono::duration_cast<std::chrono::duration<float>>(now - playerTimer.second.second);
            if (_deltaTimerInvicibility.count() > 3.0) {
                playerTimer.second.second = now;
                playerTimer.second.first = true;
                struct RType::Protocol::StatePlayerData statePlayer = {
                    .id = playerTimer.first, .invincibility = static_cast<uint8_t>(false)};
                std::vector<std::byte> dataToSend =
                    Serialization::serializeData<struct RType::Protocol::StatePlayerData>(
                        statePlayer, sizeof(statePlayer));
                for (auto client : _udpServer.getListClients())
                    _udpServer.sendInformation(
                        static_cast<uint8_t>(RType::Protocol::ComponentType::TEXTURE_STATE), dataToSend, client.second);
            }
        }
    }

} // namespace RType::Server
