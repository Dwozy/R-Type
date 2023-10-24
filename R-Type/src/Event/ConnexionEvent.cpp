/*
** EPITECH PROJECT, 2023
** ConnexionEvent.cpp
** File description:
** ConnexionEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::entitySpawn(const struct rtype::Entity entity)
    {
        GameEngine::Entity newEntity = _gameEngine.registry.spawnEntity();

        std::cout << "Player : " << entity.id << " spawned !" << std::endl;
        _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(newEntity, GameEngine::NetworkIdComponent {entity.id});
        _entityManager.setPlayerEntity(entity.positionX, entity.positionY, newEntity, _gameEngine.registry);
        if (_isPlayer) {
            _entityManager.setControlPlayerEntity(newEntity, _gameEngine.registry);
            _isPlayer = false;
            _id = newEntity;
            _serverId = entity.id;
            std::cout << "I'm the player " << entity.id << std::endl;
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
