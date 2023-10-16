/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include <iostream>
#include <vector>
#include <functional>
#include "GameEngine.hpp"
#include "Registry.hpp"
#include "SparseArray.hpp"
#include "components/CameraComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/FontComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/TextureComponent.hpp"
#include "Mouse.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/DrawSystem.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/PressableSystem.hpp"
#include "utils/Vector.hpp"

void test(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms)
{
    auto &selfCol = collisions[entityId];
    auto &selfTsf = transforms[entityId];

    if (!selfCol || !selfTsf)
        return;
    for (std::size_t i = 0; i < collisions.size(); i++) {
        if (i == entityId)
            continue;
        auto &col = collisions[i];
        auto &tsf = transforms[i];

        if (!col || !tsf || !col.value().isActive)
            continue;
        selfCol.value().collider.handleCollisionFromRect(
            selfTsf.value().position, col.value().collider, tsf.value().position);
    }
}

class MenuScene : public GameEngine::IScene
{
  public:
    MenuScene(GameEngine::GameEngine &gameEngine) : _gameEngine(gameEngine){};

    void load()
    {
        GameEngine::Entity button = _gameEngine.registry.spawnEntity();
        GameEngine::Entity camera = _gameEngine.registry.spawnEntity();
        _entities.push_back(button);
        // _entities.push_back(camera);

        GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 200.0f, 200.0f)}};
        auto &camComponent = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

        _gameEngine.window.setView(camComponent.value().view);

        _gameEngine.registry.addComponent<GameEngine::TransformComponent>(button,
            GameEngine::TransformComponent{GameEngine::Vector2<float>(0, 100), GameEngine::Vector2<float>(0, 0)});
        auto &texComponent = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(
            button, GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), true, 1});
        texComponent.value().texture.load("assets/button.png", GameEngine::Rect<int>(0, 0, 144, 16));
        texComponent.value().sprite.load(texComponent.value().texture);
        texComponent.value().sprite.setRect(GameEngine::Recti(0, 0, 48, 16));
        _gameEngine.registry.addComponent<GameEngine::PressableComponent>(button,
            GameEngine::PressableComponent{GameEngine::Recti(0, 0, 48, 16), GameEngine::Recti(0, 0, 48, 16),
                GameEngine::Recti(96, 0, 48, 16), GameEngine::Recti(48, 0, 48, 16), GameEngine::defaultState, [this]() {
                    this->_gameEngine.sceneManager.unloadScene();
                    this->_gameEngine.sceneManager.loadScene("game");
                }});
    }
    void unload()
    {
        for (std::size_t i = 0; i < _entities.size(); i++)
            _gameEngine.registry.killEntity(_entities[i]);
    }

  private:
    std::vector<GameEngine::Entity> _entities;
    GameEngine::GameEngine &_gameEngine;
};

class GameScene : public GameEngine::IScene
{
  public:
    GameScene(GameEngine::GameEngine &gameEngine) : _gameEngine(gameEngine){};

    void load()
    {
        GameEngine::Entity player = _gameEngine.registry.spawnEntity();

        _entities.push_back(player);

        GameEngine::TransformComponent tsf = {
            GameEngine::Vector2<float>(0.0f, 0.0f), GameEngine::Vector2<float>(0.0f, 0.0f)};
        GameEngine::ControllableComponent con = {GameEngine::Input::Keyboard::Z, GameEngine::Input::Keyboard::Q,
            GameEngine::Input::Keyboard::S, GameEngine::Input::Keyboard::D, 100.0f};
        GameEngine::Rectf rect(0.0, 0.0, 32.0, 16.0);
        GameEngine::CollisionComponent col = {.collider = rect, .layer = 0};
        col.addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                          SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, test);

        _gameEngine.registry.addComponent<GameEngine::TransformComponent>(player, tsf);
        _gameEngine.registry.addComponent<GameEngine::ControllableComponent>(player, con);
        _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(player, col);

        auto &playerTex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(
            player, GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), true, 1});
        playerTex.value().texture.load("assets/image.png", GameEngine::Rect<int>(0, 0, 32, 16));
        playerTex.value().sprite.load(playerTex.value().texture);

        GameEngine::Entity collision = _gameEngine.registry.spawnEntity();

        _entities.push_back(collision);
        _gameEngine.registry.addComponent<GameEngine::TransformComponent>(collision,
            GameEngine::TransformComponent{GameEngine::Vector2<float>(100, 100), GameEngine::Vector2<float>(0, 0)});
        GameEngine::CollisionComponent collisionCol = {.collider = rect, .layer = 0, .isActive = true};
        _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(collision, collisionCol);

        auto &collisionTex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(
            collision, GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), true, 1});
        collisionTex.value().texture.load("assets/image.png", GameEngine::Rect<int>(0, 0, 32, 16));
        collisionTex.value().sprite.load(collisionTex.value().texture);
    }

    void unload()
    {
        for (std::size_t i = 0; i < _entities.size(); i++)
            _gameEngine.registry.killEntity(_entities[i]);
    }

  private:
    GameEngine::GameEngine &_gameEngine;
    std::vector<GameEngine::Entity> _entities;
};

int main()
{
    GameEngine::GameEngine gameEngine(600, 600, "Demo");

    gameEngine.registry.registerComponent<GameEngine::TransformComponent>();
    gameEngine.registry.registerComponent<GameEngine::ControllableComponent>();
    gameEngine.registry.registerComponent<GameEngine::CameraComponent>();
    gameEngine.registry.registerComponent<GameEngine::TextureComponent>();
    gameEngine.registry.registerComponent<GameEngine::TextComponent>();
    gameEngine.registry.registerComponent<GameEngine::CollisionComponent>();
    gameEngine.registry.registerComponent<GameEngine::PressableComponent>();

    gameEngine.sceneManager.registerScene("menu", std::make_unique<MenuScene>(gameEngine));
    gameEngine.sceneManager.registerScene("game", std::make_unique<GameScene>(gameEngine));
    gameEngine.sceneManager.loadScene("menu");

    GameEngine::PositionSystem positionSystem(gameEngine.deltaTime.getDeltaTime());
    GameEngine::ControlSystem controlSystem;
    GameEngine::DrawSystem drawSystem(gameEngine.window);
    GameEngine::CollisionSystem collisionSystem;
    GameEngine::PressableSystem pressableSystem(gameEngine.window);

    gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &,
                                      SparseArray<GameEngine::ControllableComponent> &)>,
        GameEngine::TransformComponent, GameEngine::ControllableComponent>(controlSystem);
    gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);
    gameEngine.registry
        .addSystem<std::function<void(SparseArray<GameEngine::CollisionComponent> &)>, GameEngine::CollisionComponent>(
            collisionSystem);
    gameEngine.registry.addSystem<GameEngine::PressableFunction, GameEngine::TransformComponent,
        GameEngine::TextureComponent, GameEngine::PressableComponent>(pressableSystem);
    gameEngine.registry.addSystem<
        std::function<void(SparseArray<GameEngine::TextComponent> &, SparseArray<GameEngine::TextureComponent> &)>,
        GameEngine::TextComponent, GameEngine::TextureComponent>(drawSystem);

    while (gameEngine.window.isOpen()) {
        gameEngine.deltaTime.update();
        sf::Event event;
        while (gameEngine.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameEngine.window.close();
        }
        gameEngine.registry.runSystems();
    }
    return 0;
}
