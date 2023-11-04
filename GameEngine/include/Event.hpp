/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_
#include <any>
#include <functional>
#include <unordered_map>
#include <vector>

namespace GameEngine
{
    /// @brief value to describe the event type
    using EventType = std::size_t;
    /// @brief empty struct to describe an event that dosent provide data to subscribed functions
    struct NoEventData
    {
    };

    /// @brief enum of all event types
    enum class Event : EventType {
        WindowIsOpen,
        WindowCloseEvent,
        PollEvent,
        GetWorldMousePos,
        WindowSetView,
        SetFpsLimitEvent,
        GetTransform,
        GetCollision,
        GetTexture,
        GetControllable,
        GetNewEntity,
        GetEntity,
        GetDestroy,
        SendInput,
        GetStateTexture,
        GetScore,
        DeleteEntity,
        EnemiesSpawnedEvent,
        EnemiesMoveEvent,
        EnemiesDieEvent,
        PlayerMoveEvent,
        PlayerSpawnedEvent,
        PlayersDieEvent,
        PlayerShootEvent
    };

    /// @brief class that store all the callback functions for a specific event type
    /// @tparam EventData type of the data to send to subscribed functions when publishing events
    template <typename EventData = NoEventData>
    class EventHandler
    {
      public:
        /// @brief call all the subscribed functions with the given eventData
        /// @param eventData data to be given to subscribed functions
        void publish(EventData eventData) { _publish(eventData); }
        /// @brief call all the subscribed functions with no data (use when EventData == NoEventData)
        void publish() { _publish(NoEventData{}); }
        /// @brief register the given function to be called when the event is published
        /// @param function function to be registerer
        template <typename Function>
        void subscribe(const Function &function)
        {
            std::function<void(EventData)> callback = function;
            _callbacks.push_back(function);
        }

      private:
        /// @brief call all the subscribed functions with the given eventData
        /// @param eventData data to be given to subscribed functions
        void _publish(EventData eventData)
        {
            for (std::function<void(EventData)> callback : _callbacks)
                callback(eventData);
        }
        /// @brief vector of all subscribed functions
        std::vector<std::function<void(EventData)>> _callbacks;
    };

    /// @brief class to help create and manage all the event handlers
    class EventManager
    {
      public:
        /// @brief create a new event handler for the given event type
        /// @tparam EventData type of the data to be send to subscribed functions when the event is published
        /// @param eventType type of the event for the new event handler
        /// @return return a reference to the newly created event handler
        template <class EventData = NoEventData>
        EventHandler<EventData> &addHandler(EventType eventType)
        {
            _handlers.insert({eventType, EventHandler<EventData>()});
            return getHandler<EventData>(eventType);
        }
        /// @brief remove an event handler
        /// @param eventType event type of the handler to remove
        void removeHandler(const EventType eventType) { _handlers.erase(eventType); }
        /// @brief call all the subscribed functions with the given eventData
        /// @tparam EventData type of the data to be send to subscribed functions when the event is published
        /// @param eventType type of the event to publish
        /// @param eventData data to be given to subscribed functions
        template <class EventData = NoEventData>
        void publish(const EventType eventType, EventData eventData)
        {
            getHandler<EventData>(eventType).publish(eventData);
        }
        /// @brief return an event handler by its type
        /// @tparam EventData type of the data to send to subscribed functions when the event is published
        /// @param eventType type of the event handler to retrive
        /// @return returns a reference to the event handler obtained
        template <class EventData = NoEventData>
        EventHandler<EventData> &getHandler(const EventType eventType)
        {
            return std::any_cast<EventHandler<EventData> &>(_handlers[eventType]);
        }

      private:
        /// @brief map that store all the event handlers
        std::unordered_map<EventType, std::any> _handlers;
    };
} // namespace GameEngine

#endif /* !EVENT_HPP_ */
