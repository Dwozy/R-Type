/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** setGameEngine
*/

#include "Platformer.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/NetworkIdComponent.hpp"
#include "components/GravityComponent.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/GravitySystem.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/PauseScene.hpp"
#include "scenes/WinLoseScene.hpp"

void Platformer::setGameEngineComponent()
{
    _gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
    _gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();
    _gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
    _gameEngine.registry.registerComponent<GameEngine::CameraComponent>();
    _gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    _gameEngine.registry.registerComponent<GameEngine::TextComponent>();
    _gameEngine.registry.registerComponent<GameEngine::PressableComponent>();
    _gameEngine.registry.registerComponent<GameEngine::NetworkIdComponent>();
    _gameEngine.registry.registerComponent<GameEngine::GravityComponent>();
}

void Platformer::setGameEngineCallback()
{
}

void Platformer::setGameEngineSystem()
{
    auto drawSystem = std::make_shared<GameEngine::DrawSystem>(_gameEngine.eventManager, 1920, 1080, "GAMING");
    GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());
    GameEngine::PressableSystem pressableSystem(_gameEngine.eventManager);
    GameEngine::ControlSystem controlSystem;
    GameEngine::CollisionSystem collisionSystem;
    GameEngine::GravitySystem gravitySystem(_gameEngine.deltaTime.getDeltaTime());

    _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                       SparseArray<GameEngine::ControllableComponent> &)>,
        GameEngine::TransformComponent, GameEngine::ControllableComponent>(controlSystem);
    _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                       SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);

    _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> &)>,
    GameEngine::CollisionComponent>(collisionSystem);

    _gameEngine.registry.addSystem<GameEngine::PressableFunction, GameEngine::TransformComponent,
        GameEngine::TextureComponent, GameEngine::PressableComponent>(pressableSystem);

    _gameEngine.registry.addSystem<GameEngine::DrawSystem, GameEngine::TextComponent, GameEngine::TextureComponent>(
        drawSystem);
    _gameEngine.registry.addSystem<GameEngine::GravityFunction, GameEngine::TransformComponent, GameEngine::TextureComponent, GameEngine::GravityComponent>(gravitySystem);
}

void Platformer::setGameEngineScene()
{
    _gameEngine.sceneManager.registerScene("Game", std::make_unique<GameScene>(_gameEngine, _state, _id));
    _gameEngine.sceneManager.registerScene("Pause", std::make_unique<PauseScene>());
    _gameEngine.sceneManager.registerScene("MainMenu", std::make_unique<MainMenuScene>());
    _gameEngine.sceneManager.registerScene("WinLose", std::make_unique<WinLoseScene>(_state));
    _gameEngine.sceneManager.loadScene("MainMenu");
}

void Platformer::setGameEngineTexture() {
    _gameEngine.assetManager.loadTexture("Platformer/assets/image.png", GameEngine::Recti(0, 0, 32, 16));
    _gameEngine.assetManager.loadTexture("Platformer/assets/pata_pata.gif", GameEngine::Recti(7, 8, 17, 20));
}

void Platformer::setGameEnginePrefab() {
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/Player.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/PataPata.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/BorderMapDown.json");
}

void Platformer::setGameEngine()
{
    setGameEngineComponent();
    setGameEngineSystem();
    setGameEngineTexture();
    setGameEnginePrefab();
    setGameEngineScene();
    setGameEngineCallback();
}
