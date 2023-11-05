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
#include "systems/MusicSystem.hpp"
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
    _gameEngine.registry.registerComponent<GameEngine::HealthComponent>();
    _gameEngine.registry.registerComponent<GameEngine::MusicComponent>();
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
    GameEngine::AnimationSystem animationSystem(_gameEngine.deltaTime.getDeltaTime());
    GameEngine::MusicSystem musicSystem;

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

    _gameEngine.registry
        .addSystem<std::function<void(SparseArray<GameEngine::TextureComponent> &)>, GameEngine::TextureComponent>(
            animationSystem);

    _gameEngine.registry
        .addSystem<std::function<void(SparseArray<GameEngine::MusicComponent> &)>, GameEngine::MusicComponent>(
            musicSystem);
}

void Platformer::setGameEngineScene()
{
    _gameEngine.sceneManager.registerScene("Game", std::make_unique<GameScene>(_gameEngine, _state, _id, isJumping));
    _gameEngine.sceneManager.registerScene("Pause", std::make_unique<PauseScene>(_gameEngine, _state, isOpen));
    _gameEngine.sceneManager.registerScene("MainMenu", std::make_unique<MainMenuScene>(_gameEngine, _state));
    _gameEngine.sceneManager.registerScene("WinLose", std::make_unique<WinLoseScene>(_gameEngine, _state, isOpen));
    _gameEngine.sceneManager.loadScene("MainMenu");
}

void Platformer::setGameEngineFont() { _gameEngine.assetManager.loadFont("Platformer/assets/8-bit fortress.ttf"); }

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
    _gameEngine.prefabManager.loadPrefabFromFile("Platformer/config/UICamera.json");
}

void Platformer::setGameEngine()
{
    setGameEngineComponent();
    setGameEngineSystem();
    setGameEngineFont();
    setGameEnginePrefab();
    setGameEngineScene();
    setGameEngineCallback();
}
