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
#include "components/HealthComponent.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/PressableSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/GravitySystem.hpp"
#include "systems/CameraSystem.hpp"
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
    _gameEngine.registry.registerComponent<GameEngine::FontComponent>();
    _gameEngine.registry.registerComponent<GameEngine::TextComponent>();
    _gameEngine.registry.registerComponent<GameEngine::PressableComponent>();
    _gameEngine.registry.registerComponent<GameEngine::NetworkIdComponent>();
    _gameEngine.registry.registerComponent<GameEngine::GravityComponent>();
    _gameEngine.registry.registerComponent<GameEngine::HealthComponent>();
}

void Platformer::setGameEngineCallback() {}

void Platformer::setGameEngineSystem()
{
#ifdef DEBUG
    auto drawSystem = std::make_shared<GameEngine::DrawSystem>(
        _gameEngine.eventManager, _gameEngine.debugMenu, 1920, 1080, "SCP Adventures");
#else
    auto drawSystem = std::make_shared<GameEngine::DrawSystem>(_gameEngine.eventManager, 1920, 1080, "SCP Adventures");
#endif
    GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());
    GameEngine::PressableSystem pressableSystem(_gameEngine.eventManager);
    GameEngine::ControlSystem controlSystem;
    GameEngine::CollisionSystem collisionSystem;
    GameEngine::GravitySystem gravitySystem(_gameEngine.deltaTime.getDeltaTime());
    GameEngine::CameraSystem cameraSystem;

    _gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                       SparseArray<GameEngine::ControllableComponent> &)>,
        GameEngine::TransformComponent, GameEngine::ControllableComponent>(controlSystem);
    _gameEngine.registry
        .addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                       SparseArray<GameEngine::TextureComponent> &, SparseArray<GameEngine::GravityComponent> &)>,
            GameEngine::TransformComponent, GameEngine::TextureComponent, GameEngine::GravityComponent>(positionSystem);

    _gameEngine.registry
        .addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> &)>, GameEngine::CollisionComponent>(
            collisionSystem);

    _gameEngine.registry.addSystem<GameEngine::PressableFunction, GameEngine::TransformComponent,
        GameEngine::TextureComponent, GameEngine::PressableComponent>(pressableSystem);

    _gameEngine.registry.addSystem<GameEngine::DrawSystem, GameEngine::TextComponent, GameEngine::TextureComponent,
        GameEngine::CameraComponent>(drawSystem);
    _gameEngine.registry.addSystem<GameEngine::GravityFunction, GameEngine::GravityComponent>(gravitySystem);

    _gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::CameraComponent> &, SparseArray<GameEngine::TransformComponent> &)>,
        GameEngine::CameraComponent, GameEngine::TransformComponent>(cameraSystem);
}

void Platformer::setGameEngineScene()
{
    _gameEngine.sceneManager.registerScene("Game", std::make_unique<GameScene>(_gameEngine, _state, _id, isJumping));
    _gameEngine.sceneManager.registerScene("Pause", std::make_unique<PauseScene>(_gameEngine, _state, isOpen));
    _gameEngine.sceneManager.registerScene("MainMenu", std::make_unique<MainMenuScene>(_gameEngine, _state));
    _gameEngine.sceneManager.registerScene("WinLose", std::make_unique<WinLoseScene>(_gameEngine, _state, isOpen));
    _gameEngine.sceneManager.loadScene("MainMenu");
}

void Platformer::setGameEngineTexture()
{
    _gameEngine.assetManager.loadTexture("Platformer/assets/SCP-745.png", GameEngine::Recti(0, 64, 64, 64));
    _gameEngine.assetManager.loadTexture("Platformer/assets/box.png", GameEngine::Recti(0, 0, 32, 32));
    _gameEngine.assetManager.loadTexture(
        "Platformer/assets/dark_city_background.png", GameEngine::Recti(0, 0, 5000, 500));
    _gameEngine.assetManager.loadTexture("Platformer/assets/Gunner_Black_Run.png", GameEngine::Recti(0, 0, 48, 48));
    _gameEngine.assetManager.loadTexture("Platformer/assets/button.png", GameEngine::Recti(0, 0, 48, 16));
    _gameEngine.assetManager.loadFont("Platformer/assets/8-bit fortress.ttf");
}

void Platformer::setGameEnginePrefab()
{
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/Player.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/BorderMapDown.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/MainCam.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/MinimapCam.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/Box.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/Background.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/Enemy.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/Spike.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/buttonResume.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/buttonQuit.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/buttonRestart.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/Heart.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/EndOfLevel.json");
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/InvisibleWall.json");
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
