/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** printDTimeSystem
*/

#ifndef PRINTDTIMESYSTEM_HPP_
    #define PRINTDTIMESYSTEM_HPP_
    #include <iostream>
    #include "System.hpp"

namespace GameEngine
{
    class printDTimeSystem : public SystemBase
    {
        public:
            printDTimeSystem(GameEngine &gameEngine): SystemBase(gameEngine) {};
        protected:
            void _updateSingle(const Entity &entity) override
            {
                std::cout << this->_gameEngine.getDeltaTime() << std::endl;
            };
    };
}

#endif /* !PRINTDTIMESYSTEM_HPP_ */
