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
    class DeltaTime
    {
        public:
            DeltaTime();
            ~DeltaTime() = default;

            void update();
            const float &getDeltaTime() const;
        private:
            std::chrono::steady_clock::time_point _lastTime;
            float _deltaTime;
    };
}

#endif /* !DELTATIME_HPP_ */
