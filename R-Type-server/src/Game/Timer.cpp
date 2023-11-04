/*
** EPITECH PROJECT, 2023
** Timer.cpp
** File description:
** Timer
*/

#include "RTypeServer.hpp"

namespace RType::Server
{
    void RType::Server::RTypeServer::setTimers()
    {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        srand(time(0));

        _timers["patapata"] = now;
        _timers["dop"] = now;
        _timers["gameloop"] = now;
        _timers["charged"] = now;
    }

    void RType::Server::RTypeServer::handlingTimers()
    {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        std::chrono::duration<float> _deltaTime =
            std::chrono::duration_cast<std::chrono::duration<float>>(now - _timers["gameloop"]);
        std::chrono::duration<float> _deltaTimeChargedAttack =
            std::chrono::duration_cast<std::chrono::duration<float>>(now - _timers["charged"]);

        if (_deltaTime.count() > 0.1) {
            broadcastInformation();
            _timers["gameloop"] = now;
        }
        if (_deltaTimeChargedAttack.count() > 5.0) {
            _chargedAttack = true;
            _timers["charged"] = now;
        }
        spawnMob(now);
        handleImmunity(now);
    }
} // namespace RType::Server
