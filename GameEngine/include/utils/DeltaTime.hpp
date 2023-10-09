/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** DeltaTime
*/

#ifndef DELTATIME_HPP_
#define DELTATIME_HPP_
#include <chrono>

namespace GameEngine
{
    /// @brief DeltaTime class which handles the delta time.
    class DeltaTime
    {
      public:
        DeltaTime();
        ~DeltaTime() = default;

        /// @brief Updates the delta time.
        void update();
        /// @brief Getter for the delta time.
        /// @return The delta time in constant float.
        const float &getDeltaTime() const;

      private:
        std::chrono::steady_clock::time_point _lastTime;
        float _deltaTime;
    };
} // namespace GameEngine

#endif /* !DELTATIME_HPP_ */
