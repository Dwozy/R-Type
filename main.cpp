#include <iostream>
#include "GameEngine.hpp"
#include "utils/SafeEntity.hpp"
#include "components/Transform.hpp"
#include "utils/Vector.hpp"

int main(int ac, char const * const *av)
{
    GameEngine::GameEngine gameEngine(10);
    GameEngine::SafeEntity test(gameEngine);
    GameEngine::TransformComponent trans = { GameEngine::Vector2<float>(5.0, 10.0), GameEngine::Vector2<float>(1.0, 0.0) };

    gameEngine.registerComponent<GameEngine::TransformComponent>();
    gameEngine.assignComponent<GameEngine::TransformComponent>(test.get(), trans);
    std::cout << "HERE" << std::endl;
    while (true)
    {
        gameEngine.updateDeltaTime();
    }
    return (0);
}
