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
        if (selfCol.value().collider.isColliding(selfTsf.value().position, col.value().collider, tsf.value().position))
            tsf.value().position.x = 199;
    }
}

namespace RType::Client
{
    void RTypeClient::entitySpawn(const struct rtype::Entity entity)
    {
        GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity();

        std::cout << "Player : " << entity.id << " spawned !" << std::endl;
        _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
            newEntity, GameEngine::NetworkIdComponent{entity.id});
        _entityManager.setPlayerEntity(entity, newEntity, _gameEngine.registry);
        if (_isPlayer) {
            _entityManager.setControlPlayerEntity(newEntity, _gameEngine.registry);
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

            GameEngine::Entity parallax1 = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
                parallax1, GameEngine::TransformComponent{
                               GameEngine::Vector2<float>(0.0, 0.0), GameEngine::Vector2<float>(-50, 0.0)});
            GameEngine::Rectf collider(199, 0, 30, 200);
            GameEngine::CollisionComponent col = {.collider = collider, .layer = 10};
            _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(parallax1, col);

            auto &parallax1Tex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(parallax1,
                GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), false, {}, 0, true, 0, 0, 0});
            parallax1Tex.value().texture.load("R-Type/assets/parallax.png", GameEngine::Rect<int>(0, 0, 1080, 1080));
            parallax1Tex.value().sprite.load(parallax1Tex.value().texture);
            parallax1Tex.value().sprite.setScale(0.1851, 0.1851);

            GameEngine::Entity parallax2 = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
                parallax2, GameEngine::TransformComponent{
                               GameEngine::Vector2<float>(199.0, 0.0), GameEngine::Vector2<float>(-50, 0.0)});
            auto &col2 = _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(
                parallax2, GameEngine::CollisionComponent{.collider = collider, .layer = 10});

            auto &parallax2Tex = _gameEngine.registry.addComponent<GameEngine::TextureComponent>(parallax2,
                GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), false, {}, 0, true, 0, 0, 0});
            parallax2Tex.value().texture.load("R-Type/assets/parallax.png", GameEngine::Rect<int>(0, 0, 1080, 1080));
            parallax2Tex.value().sprite.load(parallax2Tex.value().texture);
            parallax2Tex.value().sprite.setScale(0.1851, 0.1851);

            GameEngine::Entity parallaxRange = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::TransformComponent>(
                parallaxRange, GameEngine::TransformComponent{
                                   GameEngine::Vector2<float>(-20.0, 0), GameEngine::Vector2<float>(0.0, 0.0)});
            auto &parRange = _gameEngine.registry.addComponent<GameEngine::CollisionComponent>(parallaxRange,
                GameEngine::CollisionComponent{.collider = GameEngine::Rectf(0, 0, 20, 200), .layer = 11});
            parRange.value()
                .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                               SparseArray<GameEngine::TransformComponent> &)>,
                    GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                    _gameEngine.registry, parallaxCollision);
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
