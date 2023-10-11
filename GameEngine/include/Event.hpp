/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Event
*/

#ifndef EVENT_HPP_
    #define EVENT_HPP_
    #include <functional>
    #include <unordered_map>
    #include <vector>
    #include <any>

namespace GameEngine
{
    using EventType = std::size_t;
    struct NoEventData{};

    enum class Event: EventType
    {
        WindowCloseEvent = 0,
        EnnemiesSpawnedEvent = 1,
        EnnemiesMoveEvent = 2,
        EnnemiesDieEvent = 3,
        PlayerMoveEvent =  4,
        PlayerSpawnedEvent = 5,
        PlayersDieEvent = 6,
        ShoothrowEvent = 7,
    };

    template <typename EventData=NoEventData>
    class EventHandler
    {
        public:
            void publish(EventData event) { _publish(event); }
            void publish() { _publish(NoEventData{}); }
            template <typename Function>
            void subscribe(const Function &function)
            {
                std::function<void(const EventData)> callback = function;
                _callbacks.push_back(function);
            }
        private:
            void _publish(EventData event)
            {
                for (std::function<void(const EventData)> callback: _callbacks)
                    callback(event);
            }
            std::vector<std::function<void(const EventData)>> _callbacks;
    };

    class EventManager
    {
        public:
            template <class EventData=NoEventData>
            EventHandler<EventData> &addHandler(Event eventType)
            {
                _handlers.insert({ eventType, EventHandler<EventData>()});
                return getHandler<EventData>(eventType);
            }

            void removeHandler(const Event eventType) { _handlers.erase(eventType); }
            template <class EventData=NoEventData>
            void publish(const Event eventType, EventData event) { getHandler<EventData>(eventType).publish(event); }
            template <class EventData=NoEventData>
            EventHandler<EventData> &getHandler(const Event eventType)
            {
                return std::any_cast<EventHandler<EventData> &>(_handlers[eventType]);
            }

        private:
            std::unordered_map<Event, std::any> _handlers;
    };

}

#endif /* !EVENT_HPP_ */
