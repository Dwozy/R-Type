/*
** EPITECH PROJECT, 2023
** Plazza
** File description:
** SafeQueue
*/

#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>
#include "ISafeQueue.hpp"

/// @brief A queue class that is thread safe
/// @tparam T The type contained in the queue
template <typename T>
class SafeQueue : public ISafeQueue<T> {
    public:
        SafeQueue() = default;
        /// Destructor
        ~SafeQueue() = default;
        /// @brief Push in queue, lock a mutex while pushing the value
        /// @param value Value to be pushed
        void push(T value) override
        {
            std::unique_lock<std::mutex> l(mutex);
            queue.push(value);
            cond.notify_one();
        }

        /// @brief Try to pop a value from the queue, lock a mutex while trying to pop the value
        /// @param value Reference to be filled withthe popped value
        /// @return true if the value was successfully popped, false if there was no value in queue
        bool tryPop(T &value) override
        {
            std::unique_lock<std::mutex> l(mutex);
            if (queue.size() == 0)
                return false;
            value = queue.front();
            queue.pop();
            return true;
        }

        /// @brief Pop a value from the queue, lock a mutex and wait if the queue is empty
        /// @return The popped value
        T pop() override
        {
            std::unique_lock<std::mutex> l(mutex);
            if (queue.size() == 0)
                cond.wait(l);
            T value = queue.front();
            queue.pop();
            return value;
        }

        /// @brief Returns the current size of the queue.
        /// @return size_t of the size of the queue.
        size_t size() const
        {
            return queue.size();
        }

    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable cond;
};
