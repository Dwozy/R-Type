/*
** EPITECH PROJECT, 2023
** R-Type-epitech
** File description:
** Debug
*/

#ifndef DEBUG_HPP_
#define DEBUG_HPP_
#include <imgui.h>
#include "Event.hpp"
#include <iostream>

namespace Debug
{


    class DebugMenu
    {
      public:
        void setDebugCallback(GameEngine::EventManager &eventManager)
        {
            std::cout << "setDebugCallback" << std::endl;
        }
    };
} // namespace Debug
#endif /* !DEBUG_HPP_ */
