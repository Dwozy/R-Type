/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Event
*/

#include "Event.hpp"

namespace GameEngine
{
    EventListener &EventMananger::addListener(EventType eventType)
    {
        EventListener listener;

        _listeners.insert({ eventType, listener });
        return listener;
    }
}
