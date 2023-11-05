/*
** EPITECH PROJECT, 2023
** R-Type perso
** File description:
** CollisionCallbacks
*/

#include "SparseArray.hpp"
#include "utils/CollisionsUtils.hpp"
#include "components/TransformComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/GravityComponent.hpp"
#include "components/HealthComponent.hpp"
#include "scenes/GameScene.hpp"

void standardGravityCollisionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms,
    SparseArray<GameEngine::GravityComponent> &gravity)
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
        selfGrav.value().cumulatedGVelocity = {0, 0};
        selfGrav.value().isActive = false;
    } else
        selfGrav.value().isActive = true;
}

void changeDirGravityCollisionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms,
    SparseArray<GameEngine::GravityComponent> &gravity)
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
        else if (result == 0)
            selfTsf->velocity.x = -selfTsf->velocity.x;
    }
    if (hasCollidedOnTop) {
        selfGrav.value().cumulatedGVelocity = {0, 0};
        selfGrav.value().isActive = false;
    } else
        selfGrav.value().isActive = true;
}

void GameScene::playerCollisionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms,
    SparseArray<GameEngine::GravityComponent> &gravity, SparseArray<GameEngine::HealthComponent> &health)
{
    auto &selfCol = collisions[entityId];
    auto &selfTsf = transforms[entityId];
    auto &selfGrav = gravity[entityId];
    auto &selfHealth = health[entityId];

    bool hasCollidedOnTop = false;
    if (!selfCol || !selfTsf || !selfGrav)
        return;
    for (std::size_t i = 0; i < collisions.size(); i++) {
        if (i == entityId)
            continue;
        auto &col = collisions[i];
        auto &tsf = transforms[i];
        auto &hth = health[i];

        if (!col || !tsf || !col.value().isActive || (col.value().layer != 30 && col.value().layer != 20))
            continue;
        auto result = GameEngine::replaceOnTop(selfTsf->position, selfCol->collider, tsf->position, col->collider);
        if (result == 1) {
            hasCollidedOnTop = true;
            if (hth)
                hth->health -= 1;
            if (col->layer == 20 && (std::chrono::steady_clock::now() - lastTime).count() > 1000000000) {
                lastTime = std::chrono::steady_clock::now();
                if (selfHealth->health > 0) {
                    auto lastHeart = _heartEntities.back();
                    _entities.erase(std::find(_entities.begin(), _entities.end(), lastHeart));
                    _heartEntities.pop_back();
                    _gameEngine.registry.killEntity(lastHeart);
                }
                selfHealth->health -= 1;
            }
        } else if (result == 0 && hth && selfHealth &&
                   (std::chrono::steady_clock::now() - lastTime).count() > 1000000000) {
            lastTime = std::chrono::steady_clock::now();
            if (selfHealth->health > 0) {
                auto lastHeart = _heartEntities.back();
                _entities.erase(std::find(_entities.begin(), _entities.end(), lastHeart));
                _heartEntities.pop_back();
                _gameEngine.registry.killEntity(lastHeart);
            }
            selfHealth->health -= 1;
        }
    }
    if (hasCollidedOnTop) {
        if (entityId == _id)
            _jumping = false;
        selfGrav.value().cumulatedGVelocity = {0, 0};
        selfGrav.value().isActive = false;
    } else
        selfGrav.value().isActive = true;
}

void GameScene::endOfLevelCollsionCallback(const std::size_t &entityId,
    SparseArray<GameEngine::CollisionComponent> &collisions, SparseArray<GameEngine::TransformComponent> &transforms)
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

        if (!col || !tsf || !col.value().isActive || col.value().layer != 10 ||
            !selfCol->collider.isColliding(selfTsf->position, col->collider, tsf->position))
            continue;
        _state = GameState::win;
    }
}
