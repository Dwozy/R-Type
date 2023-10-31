/*
** EPITECH PROJECT, 2023
** EntityManager.cpp
** File description:
** EntityManager
*/

#include "EntityManager.hpp"
#include "utils/Rect.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/ControllableComponent.hpp"

#include <iostream>

void collisionCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
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

        if (!col || !tsf || !col.value().isActive || col.value().layer != 15)
            continue;
        selfCol.value().collider.handleCollisionFromRect(
            selfTsf.value().position, col.value().collider, tsf.value().position);
        // selfTsf.value().velocity.x = 0;
        // selfTsf.value().velocity.y = 0;
    }
}

// void destroyShootCallback(const std::size_t &entityId, SparseArray<GameEngine::CollisionComponent> &collisions,
//     SparseArray<GameEngine::TransformComponent> &transforms)
// {
//     auto &selfCol = collisions[entityId];
//     auto &selfTsf = transforms[entityId];

//     if (!selfCol || !selfTsf)
//         return;
//     for (std::size_t i = 0; i < collisions.size(); i++) {
//         if (i == entityId)
//             continue;
//         auto &col = collisions[i];
//         auto &tsf = transforms[i];

//         if (!col || !tsf || !col.value().isActive || col.value().layer != 20)
//             continue;
//         if (selfCol.value().collider.isColliding(
//                 selfTsf.value().position, col.value().collider, tsf.value().position)) {
//             std::cout << "Shoot Down" << std::endl;
//         }
//     }
// }

void GameEngine::EntityManager::setPlayerEntityComponent(Entity entity, Registry &registry)
{
    GameEngine::Rectf rect(0.0, 0.0, 32, 16);
    GameEngine::CollisionComponent col = {.collider = rect, .layer = 17};
    auto &playerCollider = registry.addComponent<GameEngine::CollisionComponent>(entity, col);

    playerCollider.value()
        .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                       SparseArray<GameEngine::TransformComponent> &)>,
            GameEngine::CollisionComponent, GameEngine::TransformComponent>(registry, collisionCallback);

    // auto &playerTex = registry.addComponent<GameEngine::TextureComponent>(
    //     entity, GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), true, {}, 0, true, 0, 0,
    //     1});
    // playerTex.value().texture.load("R-Type/assets/image.png", GameEngine::Rect<int>(0, 0, 32, 16));
    // playerTex.value().sprite.load(playerTex.value().texture);
}

void GameEngine::EntityManager::setShootEntityComponent(Entity entity, Registry &registry)
{
    GameEngine::Rectf rect(0, 0, 47, 15.0);
    GameEngine::CollisionComponent col = {.collider = rect, .layer = 20};
    // col.addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
    //                   SparseArray<GameEngine::TransformComponent> &)>,
    //     GameEngine::CollisionComponent, GameEngine::TransformComponent>(registry, destroyShootCallback);
    // registry.addComponent<GameEngine::CollisionComponent>(entity, col);

    // auto &playerTex = registry.addComponent<GameEngine::TextureComponent>(
    //     entity, GameEngine::TextureComponent{GameEngine::Texture(), GameEngine::Sprite(), true, {}, 0, true, 0, 0,
    //     1});
    // playerTex.value().texture.load("R-Type/assets/r-typesheet1.gif", GameEngine::Rect<int>(168, 135, 47, 15));
    // playerTex.value().sprite.load(playerTex.value().texture);
}

void GameEngine::EntityManager::setEntityFromClient(struct rtype::Entity entityInfo, Entity entity, Registry &registry)
{
    GameEngine::TransformComponent tsf = {GameEngine::Vector2<float>(entityInfo.positionX, entityInfo.positionY),
        GameEngine::Vector2<float>(entityInfo.directionX, entityInfo.directionY)};
    registry.addComponent<GameEngine::TransformComponent>(entity, tsf);

    switch (entityInfo.idTexture) {
    case static_cast<uint8_t>(rtype::EntityType::PLAYER):
        setPlayerEntityComponent(entity, registry);
        break;
    case static_cast<uint8_t>(rtype::EntityType::SHOOT):
        setShootEntityComponent(entity, registry);
        break;
    }
}

void GameEngine::EntityManager::setControlPlayerEntity(Entity entity, Registry &registry)
{
    GameEngine::ControllableComponent con = {GameEngine::Input::Keyboard::Z, GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S, GameEngine::Input::Keyboard::D, 100.0f};
    registry.addComponent<GameEngine::ControllableComponent>(entity, con);
}

void GameEngine::EntityManager::setEntity(struct rtype::Entity entityInfo, Entity entity, Registry &registry)
{
    GameEngine::TransformComponent tsf = {GameEngine::Vector2<float>(entityInfo.positionX, entityInfo.positionY),
        GameEngine::Vector2<float>(entityInfo.directionX, entityInfo.directionY)};
    registry.addComponent<GameEngine::TransformComponent>(entity, tsf);
    GameEngine::Rectf rect(0.0, 0.0, 32.0, 16.0);
    GameEngine::CollisionComponent col = {.collider = rect, .layer = 17};
    col.addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                      SparseArray<GameEngine::TransformComponent> &)>,
        GameEngine::CollisionComponent, GameEngine::TransformComponent>(registry, collisionCallback);
    registry.addComponent<GameEngine::CollisionComponent>(entity, col);
}
