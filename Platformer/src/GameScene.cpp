/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GameScene
*/

#include <iostream>
#include <functional>
#include <algorithm>
#include "scenes/GameScene.hpp"
#include "utils/CollisionsUtils.hpp"

void GameScene::load()
{
    std::cout << "Loading GameScene" << std::endl;
    if (_isLoaded && _state == GameState::Restart) {
        for (std::size_t i = 0; i < _entities.size(); i++) {
            _gameEngine.registry.killEntity(_entities[i]);
        }
        _entities.clear();
    }
    if (_state == GameState::Mainmenu || _state == GameState::Restart) {
        std::cout << "create game from start" << std::endl;
        _isLoaded = true;
        auto minimap_camera = _gameEngine.prefabManager.createEntityFromPrefab("minimap_camera", _gameEngine.registry);

        _id = _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry);
        _entities.push_back(_gameEngine.registry.getEntityById(_id));

        auto health = _gameEngine.registry.getComponent<GameEngine::HealthComponent>()[_id];
        int i = 0;
        float y = 0;
        float size = 0;
        for (; health && i < health->health; i++) {
            auto heart = _gameEngine.prefabManager.createEntityFromPrefab("heart", _gameEngine.registry);
            _entities.push_back(heart);
            _heartEntities.push_back(heart);
            auto &heartTransfrom = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[heart];
            size = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[heart]->textureSize.width;
            heartTransfrom->position.x = i * size;
            y = heartTransfrom->position.y;
        }
        auto heartCam = _gameEngine.registry.spawnEntity();
        _entities.push_back(heartCam);
        auto &heartCamComp = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(
            heartCam, GameEngine::CameraComponent{GameEngine::View(GameEngine::Rectf(0, y, i * size, size))});
        heartCamComp->view.setViewPort(GameEngine::Vector2<float>(0.01, 0.9), 0.05 * i, 0.1);

        auto camera = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
        _entities.push_back(camera);
        _entities.push_back(minimap_camera);

        std::cout << "player is " << _id << std::endl;

        auto &camComponent = _gameEngine.registry.getComponent<GameEngine::CameraComponent>()[camera];
        camComponent->target = _id;

        auto playerCollisionCallbackBind = std::bind(&GameScene::playerCollisionCallback, this, std::placeholders::_1,
            std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
        auto endOfLevelCollisionCallbackBind = std::bind(&GameScene::endOfLevelCollsionCallback, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

        auto &col = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[_id];
        col->addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::GravityComponent> &,
                           SparseArray<GameEngine::HealthComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent, GameEngine::GravityComponent,
            GameEngine::HealthComponent>(_gameEngine.registry, playerCollisionCallbackBind);
        col->addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(
            _gameEngine.registry, endOfLevelCollisionCallbackBind);

        GameEngine::Entity background =
            _gameEngine.prefabManager.createEntityFromPrefab("background", _gameEngine.registry);
        _entities.push_back(background);

        auto block = _gameEngine.prefabManager.createEntityFromPrefab("invisible_wall", _gameEngine.registry);
        auto block2 = _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry);
        _entities.push_back(block);
        _entities.push_back(block2);

        auto end = _gameEngine.prefabManager.createEntityFromPrefab("end_of_level", _gameEngine.registry);
        _entities.push_back(end);

        _mapLoader.loadMap("Platformer/maps/map1",
            {0, _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[block2]->position.y - 7 * 32}, 32);
        _state = GameState::Game;
    }
    if (_state == GameState::Pause) {
        auto &cams = _gameEngine.registry.getComponent<GameEngine::CameraComponent>();
        auto &colls = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>();
        auto &ctrls = _gameEngine.registry.getComponent<GameEngine::ControllableComponent>();
        auto &Gravs = _gameEngine.registry.getComponent<GameEngine::GravityComponent>();
        auto &Press = _gameEngine.registry.getComponent<GameEngine::PressableComponent>();
        auto &Texts = _gameEngine.registry.getComponent<GameEngine::TextComponent>();
        auto &Textures = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();
        auto &Trs = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
        cams = camcpy;
        colls = collscpy;
        ctrls = ctrlscpy;
        Gravs = gravscpy;
        Press = presscpy;
        Texts = textscpy;
        Textures = texturescpy;
        Trs = trscpy;
        std::cout << "resume game" << std::endl;
        _state = GameState::Game;
    }
}

void GameScene::unload()
{
    camcpy = _gameEngine.registry.getComponent<GameEngine::CameraComponent>();
    collscpy = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>();
    ctrlscpy = _gameEngine.registry.getComponent<GameEngine::ControllableComponent>();
    gravscpy = _gameEngine.registry.getComponent<GameEngine::GravityComponent>();
    presscpy = _gameEngine.registry.getComponent<GameEngine::PressableComponent>();
    textscpy = _gameEngine.registry.getComponent<GameEngine::TextComponent>();
    texturescpy = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();
    trscpy = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
    auto &cams = _gameEngine.registry.getComponent<GameEngine::CameraComponent>();
    auto &colls = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>();
    auto &ctrls = _gameEngine.registry.getComponent<GameEngine::ControllableComponent>();
    auto &gravs = _gameEngine.registry.getComponent<GameEngine::GravityComponent>();
    auto &press = _gameEngine.registry.getComponent<GameEngine::PressableComponent>();
    auto &texts = _gameEngine.registry.getComponent<GameEngine::TextComponent>();
    auto &textures = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();
    auto &trs = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
    for (size_t i = 0; i < cams.size(); ++i) {
        auto &cam = cams[i];
        if (cam)
            cam->isActive = false;
    }
    for (size_t i = 0; i < colls.size(); ++i) {
        auto &col = colls[i];
        if (col)
            col->isActive = false;
    }
    for (size_t i = 0; i < ctrls.size(); ++i) {
        auto &ctrl = ctrls[i];
        if (ctrl) {
            ctrl->key_up = GameEngine::Input::Keyboard::Key::NO_KEY;
            ctrl->key_left = GameEngine::Input::Keyboard::Key::NO_KEY;
            ;
            ctrl->key_down = GameEngine::Input::Keyboard::Key::NO_KEY;
            ;
            ctrl->key_right = GameEngine::Input::Keyboard::Key::NO_KEY;
            ;
        }
    }
    for (size_t i = 0; i < gravs.size(); ++i) {
        auto &gra = gravs[i];
        if (gra) {
            gra->isActive = false;
            gra->cumulatedGVelocity = GameEngine::Vector2{0.0f, 0.0f};
        }
    }
    for (size_t i = 0; i < press.size(); ++i) {
        auto &pres = press[i];
        if (pres) {
            pres->hitbox = GameEngine::Recti(0, 0, 0, 0);
        }
    }
    for (size_t i = 0; i < texts.size(); ++i) {
        auto &tex = texts[i];
        if (tex) {
            tex->isRendered = false;
        }
    }
    for (size_t i = 0; i < textures.size(); ++i) {
        auto &tex = textures[i];
        if (tex) {
            tex->isRendered = false;
        }
    }
    for (size_t i = 0; i < trs.size(); ++i) {
        auto &tf = trs[i];
        if (tf) {
            tf->velocity = GameEngine::Vector2<float>{0.0f, 0.0f};
        }
    }
    std::cout << "unloading GameScene" << std::endl;
}

void GameScene::update()
{
    auto &playerHealth = _gameEngine.registry.getComponent<GameEngine::HealthComponent>()[_id];
    if (playerHealth && playerHealth->health <= 0) {
        _state = GameState::Lose;
    }
    for (auto iter = _entities.begin(); iter != _entities.end();) {
        auto &hth = _gameEngine.registry.getComponent<GameEngine::HealthComponent>()[*iter];
        if (hth && hth->health <= 0) {
            _gameEngine.registry.killEntity(*iter);
            iter = _entities.erase(iter);
        } else
            iter++;
    }
}
