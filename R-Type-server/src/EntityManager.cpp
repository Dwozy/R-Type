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

        if (!col || !tsf || !col.value().isActive)
            continue;
        selfCol.value().collider.handleCollisionFromRect(
            selfTsf.value().position, col.value().collider, tsf.value().position);
    }
}

void GameEngine::EntityManager::setPlayerEntity(float posX, float posY, Entity entity, Registry &registry)
{
    GameEngine::TransformComponent tsf = {
        GameEngine::Vector2<float>(posX, posY), GameEngine::Vector2<float>(0.0f, 0.0f)};
    registry.addComponent<GameEngine::TransformComponent>(entity, tsf);
    GameEngine::Rectf rect(0.0, 0.0, 32.0, 16.0);
    GameEngine::CollisionComponent col = {.collider = rect, .layer = 0};
    col.addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                      SparseArray<GameEngine::TransformComponent> &)>,
        GameEngine::CollisionComponent, GameEngine::TransformComponent>(registry, collisionCallback);
    registry.addComponent<GameEngine::CollisionComponent>(entity, col);
    auto &playerTex = registry.addComponent<GameEngine::TextureComponent>(entity, GameEngine::TextureComponent());
    // playerTex.value().texture.load("R-Type/assets/image.png", GameEngine::Rect<int>(0, 0, 32, 16));
    // playerTex.value().sprite.load(playerTex.value().texture);
}

void GameEngine::EntityManager::setControlPlayerEntity(Entity entity, Registry &registry)
{
    GameEngine::ControllableComponent con = {GameEngine::Input::Keyboard::Z, GameEngine::Input::Keyboard::Q,
        GameEngine::Input::Keyboard::S, GameEngine::Input::Keyboard::D, 100.0f};
    registry.addComponent<GameEngine::ControllableComponent>(entity, con);
}

void GameEngine::EntityManager::setEntity(float posX, float posY, Entity entity, Registry &registry)
{
    GameEngine::TransformComponent tsf = {
        GameEngine::Vector2<float>(posX, posY), GameEngine::Vector2<float>(0.0f, 0.0f)};
    registry.addComponent<GameEngine::TransformComponent>(entity, tsf);
    GameEngine::Rectf rect(0.0, 0.0, 32.0, 16.0);
    GameEngine::CollisionComponent col = {.collider = rect, .layer = 0};
    col.addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                      SparseArray<GameEngine::TransformComponent> &)>,
        GameEngine::CollisionComponent, GameEngine::TransformComponent>(registry, collisionCallback);
    registry.addComponent<GameEngine::CollisionComponent>(entity, col);
}
