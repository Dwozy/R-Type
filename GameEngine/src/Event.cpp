/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Event
*/

#include "Event.hpp"

namespace GameEngine
{
    void EventHandler::_publish(EventData event)
    {
        for (std::function<void(const EventData)> callback: _callbacks)
            callback(event);
    }
}
