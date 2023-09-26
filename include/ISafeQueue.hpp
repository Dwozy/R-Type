/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** ISafeQueue
*/

#pragma once

/// @brief Interface for queue that is thread safe
/// @tparam T The type contained in the queue
template <typename T>
class ISafeQueue {
    public:
        /// Destructor
        virtual ~ISafeQueue() = default;
        /// @brief Push in queue
        /// @param value Value to be pushed
        virtual void push(T value) = 0;
        /// @brief Try to pop a value from the queue
        /// @param value Reference to be filled withthe popped value
        /// @return true if the value was successfully popped, false otherwise
        virtual bool tryPop(T &value) = 0;
        /// @brief Pop a value from the queue
        /// @return The popped value
        virtual T pop() = 0;
};
