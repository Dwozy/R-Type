/*
** EPITECH PROJECT, 2023
** SetupGame.cpp
** File description:
** SetupGame
*/

#include "RTypeServer.hpp"

namespace RType::Server
{

    void RTypeServer::setupGame()
    {
        auto destroyCallback = std::bind(&RType::Server::RTypeServer::destroyEntityCallback, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

        auto rightBoxEntity =
            _gameEngine.prefabManager.createEntityFromPrefab("destroy_right_box", _gameEngine.registry, false);
        auto &rightBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[rightBoxEntity];
        rightBox.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyCallback);
        _listIdType.insert({static_cast<uint16_t>(rightBoxEntity), static_cast<uint8_t>(rtype::EntityType::NONE)});

        auto leftBoxEntity =
            _gameEngine.prefabManager.createEntityFromPrefab("destroy_left_box", _gameEngine.registry, false);
        auto &leftBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[leftBoxEntity];
        leftBox.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry, destroyCallback);
        _listIdType.insert({static_cast<uint16_t>(leftBoxEntity), static_cast<uint8_t>(rtype::EntityType::NONE)});

        auto borderBoxUp =
            _gameEngine.prefabManager.createEntityFromPrefab("border_map_up", _gameEngine.registry, false);
        _listIdType.insert({static_cast<uint16_t>(borderBoxUp), static_cast<uint8_t>(rtype::EntityType::NONE)});

        auto borderBoxDown =
            _gameEngine.prefabManager.createEntityFromPrefab("border_map_down", _gameEngine.registry, false);
        _listIdType.insert({static_cast<uint16_t>(borderBoxDown), static_cast<uint8_t>(rtype::EntityType::NONE)});

        auto borderBoxLeft =
            _gameEngine.prefabManager.createEntityFromPrefab("border_map_left", _gameEngine.registry, false);
        _listIdType.insert({static_cast<uint16_t>(borderBoxLeft), static_cast<uint8_t>(rtype::EntityType::NONE)});

        auto borderBoxRight =
            _gameEngine.prefabManager.createEntityFromPrefab("border_map_right", _gameEngine.registry, false);
        _listIdType.insert({static_cast<uint16_t>(borderBoxRight), static_cast<uint8_t>(rtype::EntityType::NONE)});
    }
} // namespace RType::Server
