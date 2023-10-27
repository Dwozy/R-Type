/*
** EPITECH PROJECT, 2023
** ConnexionEvent.cpp
** File description:
** ConnexionEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

void parallaxCollision(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
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

        if (!col || !tsf || !col.value().isActive || col.value().layer != 10)
            continue;
        if (selfCol.value().collider.isColliding(
                selfTsf.value().position, col.value().collider, tsf.value().position)) {
            tsf.value().position.x = 199;
        }
    }
}

void collisionEntityCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
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

        if (!col || !tsf || !col.value().isActive || col.value().layer != 25)
            continue;
        selfCol.value().collider.handleCollisionFromRect(selfTsf.value().position, col.value().collider, tsf.value().position);
    }
}

namespace RType::Client
{
    void RTypeClient::entitySpawn(const struct rtype::Entity entity)
    {
        if (!_isPlayer) {
            auto newEntity =
                _gameEngine.prefabManager.createEntityFromPrefab("non_player_starship", _gameEngine.registry);
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                newEntity, GameEngine::NetworkIdComponent{entity.id});
            auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[newEntity];
            texture->sprite.load(_gameEngine.assetManager.getTexture(texture->path));
        }
        if (_isPlayer) {
            std::cout << "PLAYER SPAWN" << std::endl;
            auto newEntity = _gameEngine.prefabManager.createEntityFromPrefab("player", _gameEngine.registry);
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                newEntity, GameEngine::NetworkIdComponent{entity.id});
            auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[newEntity];
            texture->sprite.load(_gameEngine.assetManager.getTexture(texture->path));
            auto &entityCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[newEntity];
            entityCollider.value()
                .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, collisionEntityCallback);
            _isPlayer = false;
            _id = newEntity;
            _serverId = entity.id;
            std::cout << "I'm the player " << entity.id << std::endl;

            GameEngine::Entity camera = _gameEngine.registry.spawnEntity();
            GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 200.0f, 200.0f)}};
            auto &refCamera = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);
            if (refCamera)
                _gameEngine.eventManager.publish<GameEngine::View &>(
                    GameEngine::Event::WindowSetView, refCamera.value().view);

            auto parallax1 = _gameEngine.prefabManager.createEntityFromPrefab("parallax", _gameEngine.registry);
            auto &textureParallax = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[parallax1];
            textureParallax->sprite.load(_gameEngine.assetManager.getTexture(textureParallax->path));
            textureParallax->sprite.setScale(0.1851, 0.1851);

            auto parallax2 = _gameEngine.prefabManager.createEntityFromPrefab("parallax", _gameEngine.registry);
            auto &posParallax2 = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[parallax2];
            posParallax2.value().position = GameEngine::Vector2<float>(199.0, 0.0);
            auto &textureParallax2 = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[parallax2];
            textureParallax2->sprite.load(_gameEngine.assetManager.getTexture(textureParallax2->path));
            textureParallax2->sprite.setScale(0.1851, 0.1851);

            auto parallaxRange =
                _gameEngine.prefabManager.createEntityFromPrefab("parallaxCollision", _gameEngine.registry);
            auto &parallaxBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[parallaxRange];
            parallaxBox.value()
                .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                               SparseArray<GameEngine::TransformComponent> &)>,
                    GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                    _gameEngine.registry, parallaxCollision);

            auto borderBoxUp = _gameEngine.prefabManager.createEntityFromPrefab("border_map_up", _gameEngine.registry);

            auto borderBoxDown = _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry);

            auto borderBoxLeft = _gameEngine.prefabManager.createEntityFromPrefab("border_map_left", _gameEngine.registry);

            auto borderBoxRight = _gameEngine.prefabManager.createEntityFromPrefab("border_map_right", _gameEngine.registry);
            // GameEngine::Entity windowBoxUp = _gameEngine.registry.spawnEntity();
            // _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
            //     windowBoxUp, GameEngine::TransformComponent{
            //                    GameEngine::Vector2<float>(-20.0, -20.0), GameEngine::Vector2<float>(0.0, 0.0)});
            // _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(windowBoxUp,
            //     GameEngine::CollisionComponent{.collider = GameEngine::Rectf(0, 0, 240.0, 20.0), .layer = 15});

            // GameEngine::Entity windowBoxDown = _gameEngine.registry.spawnEntity();
            // _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
            //     windowBoxDown, GameEngine::TransformComponent{
            //                    GameEngine::Vector2<float>(-20.0, 200.0), GameEngine::Vector2<float>(0.0, 0.0)});
            // _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(windowBoxDown,
            //     GameEngine::CollisionComponent{.collider = GameEngine::Rectf(0, 0, 240.0, 20.0), .layer = 15});

            // GameEngine::Entity windowBoxLeft = _gameEngine.registry.spawnEntity();
            // _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
            //     windowBoxLeft, GameEngine::TransformComponent{
            //                    GameEngine::Vector2<float>(-20.0, -20.0), GameEngine::Vector2<float>(0.0, 0.0)});
            // _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(windowBoxLeft,
            //     GameEngine::CollisionComponent{.collider = GameEngine::Rectf(0, 0, 20.0, 240.0), .layer = 15});

            // GameEngine::Entity windowBoxRight = _gameEngine.registry.spawnEntity();
            // _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
            //     windowBoxRight, GameEngine::TransformComponent{
            //                    GameEngine::Vector2<float>(200.0, -20.0), GameEngine::Vector2<float>(0.0, 0.0)});
            // _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(windowBoxRight,
            //     GameEngine::CollisionComponent{.collider = GameEngine::Rectf(0, 0, 20.0, 240.0), .layer = 15});
        }
    }

    void RTypeClient::setConnexionCallback()
    {
        auto &refHandlerNew =
            _gameEngine.eventManager.addHandler<struct rtype::Entity>(GameEngine::Event::GetNewEntity);
        auto handleNew = std::bind(&RType::Client::RTypeClient::entitySpawn, this, std::placeholders::_1);
        refHandlerNew.subscribe(handleNew);
    }
} // namespace RType::Client
