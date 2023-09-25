#include <iostream>
#include "GameEngine.hpp"
#include "utils/SafeEntity.hpp"

int main(int ac, char const * const *av)
{
    GameEngine::GameEngine gameEngine(10);
    GameEngine::SafeEntity test(gameEngine);

    std::cout << "HERE" << std::endl;
    while (true)
    {
        gameEngine.updateDeltaTime();
    }
    return (0);
}
