#include "GameEngine.hpp"
#include "Systems/printDTimeSystem.hpp"

int main(int ac, char const * const *av)
{
    GameEngine::GameEngine gameEngine(10);
    GameEngine::Entity test = gameEngine.createEntity();
    auto sys = gameEngine.registerSystem<GameEngine::printDTimeSystem>();

    sys->entities.insert(test);
    while (1)
    {
        sys->update();
        gameEngine.updateDeltaTime();
    }
    return (0);
}
