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

namespace GameEngine
{
    using EventType = std::size_t;

    enum class Event: EventType
    {
        WindowCloseEvent = 0,
    };

    class EventHandler
    {
        public:
            void publish()
            {
                for (std::function<void()> callback: _callbacks)
                    callback();
            }
            template <typename Function>
            void subscribe(Function function)
            {
                std::function<void()> callback = [function]() {
                    function();
                };
                _callbacks.push_back(function);
            }
        private:
            std::vector<std::function<void(void)>> _callbacks;
    };

    class EventMananger
    {
        public:
            void addHandler(Event eventType, const EventHandler handler) { _handlers.insert({ eventType, handler }); }
            EventHandler &addHandler(const Event eventType);
            void removeHandler(const Event eventType) { _handlers.erase(eventType); }
            EventHandler &getHandler(const Event eventType) { return _handlers.at(eventType); }

        private:
            std::unordered_map<Event, EventHandler> _handlers;
    };

}


#endif /* !EVENT_HPP_ */
