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
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <map>

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
        QuitEvent,
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

    static const std::map<EventType, std::string> InternalEventNames{
        {static_cast<EventType>(Event::WindowIsOpen), "WindowIsOpen"},
        {static_cast<EventType>(Event::WindowCloseEvent), "WindowCloseEvent"},
        {static_cast<EventType>(Event::PollEvent), "PollEvent"},
        {static_cast<EventType>(Event::GetWorldMousePos), "GetWorldMousePos"},
        {static_cast<EventType>(Event::WindowSetView), "WindowSetView"},
        {static_cast<EventType>(Event::SetFpsLimitEvent), "SetFpsLimitEvent"},
        {static_cast<EventType>(Event::GetTransform), "GetTransform"},
        {static_cast<EventType>(Event::GetCollision), "GetCollision"},
        {static_cast<EventType>(Event::GetTexture), "GetTexture"},
        {static_cast<EventType>(Event::GetControllable), "GetControllable"},
        {static_cast<EventType>(Event::GetNewEntity), "GetNewEntity"},
        {static_cast<EventType>(Event::GetEntity), "GetEntity"},
        {static_cast<EventType>(Event::SendInput), "SendInput"},
        {static_cast<EventType>(Event::DeleteEntity), "DeleteEntity"},
        {static_cast<EventType>(Event::EnemiesSpawnedEvent), "EnemiesSpawnedEvent"},
        {static_cast<EventType>(Event::EnemiesMoveEvent), "EnemiesMoveEvent"},
        {static_cast<EventType>(Event::EnemiesDieEvent), "EnemiesDieEvent"},
        {static_cast<EventType>(Event::PlayerMoveEvent), "PlayerMoveEvent"},
        {static_cast<EventType>(Event::PlayerSpawnedEvent), "PlayerSpawnedEvent"},
        {static_cast<EventType>(Event::PlayersDieEvent), "PlayersDieEvent"},
        {static_cast<EventType>(Event::PlayerShootEvent), "PlayerShootEvent"},
    };
#ifdef DEBUG
    static const int DEFAULT_MAX_EVENT_LOG_LENGTH = 100000;
#endif

    /// @brief class that store all the callback functions for a specific event type
    /// @tparam EventData type of the data to send to subscribed functions when publishing events
    template <typename EventData = NoEventData>
    class EventHandler
    {
      public:
#ifdef DEBUG
        EventHandler(std::vector<EventType> &eventLog, const EventType eventType)
            : _eventLog(eventLog), _eventType(eventType){};
#endif
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
#ifdef DEBUG
        std::vector<EventType> &_eventLog;
#endif
        const EventType _eventType;
        /// @brief call all the subscribed functions with the given eventData
        /// @param eventData data to be given to subscribed functions
        void _publish(EventData eventData)
        {
#ifdef DEBUG
			if (_eventLog.size() >= DEFAULT_MAX_EVENT_LOG_LENGTH)
				_eventLog.clear();
            _eventLog.push_back(_eventType);
#endif
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
#ifdef DEBUG
            _handlers.insert({eventType, EventHandler<EventData>(eventLog, eventType)});
#else
            _handlers.insert({eventType, EventHandler<EventData>()});
#endif
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

#ifdef DEBUG
        std::vector<EventType> eventLog;
#endif

      private:
        /// @brief map that store all the event handlers
        std::unordered_map<EventType, std::any> _handlers;
    };

} // namespace GameEngine

#endif /* !EVENT_HPP_ */
