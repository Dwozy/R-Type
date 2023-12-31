/*
** EPITECH PROJECT, 2023
** HandlingShoot.cpp
** File description:
** HandlingShoot
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::handleShootType(
        const std::string &typeShootString, struct RType::Protocol::ShootData shootInfo, RType::TextureType typeShoot)
    {
        GameEngine::Entity shootEntity =
            _gameEngine.prefabManager.createEntityFromPrefab(typeShootString, _gameEngine.registry, false);
        GameEngine::Recti rectPlayer = {0, 0, 0, 0};
        auto &shootPos = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[shootEntity];
        auto &shootCollider = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[shootEntity];
        auto destroyShootCallback = std::bind(&RTypeServer::destroyEntityCallback, this, std::placeholders::_1,
            std::placeholders::_2, std::placeholders::_3);

        for (auto &entityTexture : _listIdType) {
            if (entityTexture.second == static_cast<uint8_t>(RType::TextureType::PLAYER)) {
                rectPlayer = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[entityTexture.first]
                                 .value()
                                 .textureRects[0];
                break;
            }
        }

        shootCollider.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(
                _gameEngine.registry, destroyShootCallback);

        shootPos->position = GameEngine::Vector2<float>(
            shootInfo.x + (rectPlayer.width / 2) - (shootCollider.value().collider.width / 2),
            shootInfo.y + (rectPlayer.height / 2) - (shootCollider.value().collider.height / 2));
        updateComponentInformation(shootEntity, typeShoot);
        broadcastEntityInformation(shootEntity);
    }

    void RTypeServer::handleShoot(struct RType::Protocol::ShootData shootInfo)
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> _deltaTimeChargedAttack =
            std::chrono::duration_cast<std::chrono::duration<float>>(now - _chargedAttackTimer.at(shootInfo.id).second);

        if (_chargedAttackTimer.find(shootInfo.id) == _chargedAttackTimer.end())
            return;
        if (_deltaTimeChargedAttack.count() > 1.5)
            handleShootType("charged_shoot", shootInfo, RType::TextureType::CHARGED_SHOOT);
        else
            handleShootType("simple_shoot", shootInfo, RType::TextureType::SIMPLE_SHOOT);
        _chargedAttackTimer.at(shootInfo.id).second = now;
    }
} // namespace RType::Server
