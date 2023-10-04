/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Event
*/

#include "Event.hpp"

namespace GameEngine
{
    EventHandler &EventMananger::addHandler(GameEngine::Event eventType)
    {
        EventHandler handler;

        _handlers.insert({ eventType, handler });
        return getHandler(eventType);
    }
}
