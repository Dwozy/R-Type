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

    class EventListener
    {
        public:
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
            void addListener(EventType eventType, const EventListener listener) { _listeners.insert({ eventType, listener }); }
            EventListener &addListener(const EventType eventType);
            void removeListener(const EventType eventType) { _listeners.erase(eventType); }
            EventListener &getListener(const EventType eventType) { return _listeners.at(eventType); }

        private:
            std::unordered_map<EventType, EventListener> _listeners;
    };

}


#endif /* !EVENT_HPP_ */
