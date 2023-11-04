/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GameScene
*/

#include "scenes/GameScene.hpp"
#include "utils/CollisionsUtils.hpp"
#include <iostream>
#include <functional>

void GameScene::BlockcollisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
    SparseArray<GameEngine::TransformComponent> &transforms, SparseArray<GameEngine::GravityComponent> &gravity)
{
    auto &selfCol = collisions[entityId];
    auto &selfTsf = transforms[entityId];
    auto &selfGrav = gravity[entityId];

    bool hasCollidedOnTop = false;

    if (!selfCol || !selfTsf || !selfGrav)
        return;
    for (std::size_t i = 0; i < collisions.size(); i++) {
        if (i == entityId)
            continue;
        auto &col = collisions[i];
        auto &tsf = transforms[i];

        if (!col || !tsf || !col.value().isActive || col.value().layer != 30)
            continue;
        auto result = GameEngine::replaceOnTop(selfTsf->position, selfCol->collider, tsf->position, col->collider);
        if (result == 1)
            hasCollidedOnTop = true;
    }
    if (hasCollidedOnTop) {
        if (entityId == _id)
            _jumping = false;
        selfGrav.value().cumulatedGVelocity = {0, 0};
        selfGrav.value().isActive = false;
    } else
        selfGrav.value().isActive = true;
}

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
        auto camera = _gameEngine.prefabManager.createEntityFromPrefab("main_camera", _gameEngine.registry);
        _entities.push_back(camera);
        _entities.push_back(minimap_camera);
        _id = _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry);
        _entities.push_back(_gameEngine.registry.getEntityById(_id));

        std::cout << "player is " << _id << std::endl;

        auto &camComponent = _gameEngine.registry.getComponent<GameEngine::CameraComponent>()[camera];
        camComponent->target = _id;

        auto bolckColliderCallback = std::bind(&GameScene::BlockcollisionCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[_id]
            .value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::GravityComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent, GameEngine::GravityComponent>(
                _gameEngine.registry, bolckColliderCallback);

        GameEngine::Entity block = _gameEngine.prefabManager.createEntityFromPrefab("box", _gameEngine.registry);
        _entities.push_back(block);
        auto &blockTransform = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[block];
        blockTransform->position = {50, 50};

        GameEngine::Entity background = _gameEngine.prefabManager.createEntityFromPrefab("background", _gameEngine.registry);
        _entities.push_back(background);
        auto enemy = _gameEngine.prefabManager.createEntityFromPrefab("enemy", _gameEngine.registry);
        _entities.push_back(enemy);
        _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[enemy]
            .value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::GravityComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent, GameEngine::GravityComponent>(
                _gameEngine.registry, bolckColliderCallback);

        GameEngine::Entity block2 =
            _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry);
        _entities.push_back(block2);
        _state = GameState::Game;
    }
    if (_state == GameState::Pause) {
        auto &cams =  _gameEngine.registry.getComponent<GameEngine::CameraComponent>();
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
    auto &cams =  _gameEngine.registry.getComponent<GameEngine::CameraComponent>();
    auto &colls = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>();
    auto &ctrls = _gameEngine.registry.getComponent<GameEngine::ControllableComponent>();
    auto &gravs = _gameEngine.registry.getComponent<GameEngine::GravityComponent>();
    auto &press = _gameEngine.registry.getComponent<GameEngine::PressableComponent>();
    auto &texts = _gameEngine.registry.getComponent<GameEngine::TextComponent>();
    auto &textures = _gameEngine.registry.getComponent<GameEngine::TextureComponent>();
    auto &trs =  _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
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
            ctrl->key_left = GameEngine::Input::Keyboard::Key::NO_KEY;;
            ctrl->key_down = GameEngine::Input::Keyboard::Key::NO_KEY;;
            ctrl->key_right = GameEngine::Input::Keyboard::Key::NO_KEY;;
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
