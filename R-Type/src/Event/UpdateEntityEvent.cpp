/*
** EPITECH PROJECT, 2023
** UpdateEntityEvent.cpp
** File description:
** UpdateEntityEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::updateEntity(const struct rtype::Entity entity)
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();

        if (_listTextureTypePrefab.find(entity.idTexture) == _listTextureTypePrefab.end())
            return;
        if (!_searchEntity(entity.id)) {
            // std::cout << _listTextureTypePrefab.at(entity.idTexture) << std::endl;
            GameEngine::Entity newEntity = _gameEngine.prefabManager.createEntityFromPrefab(
                _listTextureTypePrefab.at(entity.idTexture), _gameEngine.registry);
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                newEntity, GameEngine::NetworkIdComponent{entity.id});
            auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[newEntity];
            texture->sprite.load(_gameEngine.assetManager.getTexture(texture->path));
            auto &tsf = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[newEntity];
            tsf.value().position.x = entity.positionX;
            tsf.value().position.y = entity.positionY;
            tsf.value().velocity.x = entity.directionX;
            tsf.value().velocity.y = entity.directionY;
            return;
        }
        std::size_t id = _findEntity(entity.id);
        if (!transforms[id].has_value()) {
            GameEngine::Entity newEntity = _gameEngine.prefabManager.createEntityFromPrefab(
                _listTextureTypePrefab.at(entity.idTexture), _gameEngine.registry);
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                newEntity, GameEngine::NetworkIdComponent{entity.id});
            auto &texture = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[newEntity];
            texture->sprite.load(_gameEngine.assetManager.getTexture(texture->path));
            auto &tsf = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[newEntity];
            tsf.value().position.x = entity.positionX;
            tsf.value().position.y = entity.positionY;
            tsf.value().velocity.x = entity.directionX;
            tsf.value().velocity.y = entity.directionY;
        } else {
            transforms[id]->velocity.x = entity.directionX;
            transforms[id]->velocity.y = entity.directionY;
            transforms[id]->position.x = (fabs(transforms[id]->position.x - entity.positionX) < 2)
                                             ? transforms[id]->position.x
                                             : entity.positionX;
            transforms[id]->position.y = (fabs(transforms[id]->position.y - entity.positionY) < 2)
                                             ? transforms[id]->position.y
                                             : entity.positionY;
        }
    }

    void RTypeClient::setUpdateEntityCallback()
    {
        auto &refHandlerUpdate =
            _gameEngine.eventManager.addHandler<struct rtype::Entity>(GameEngine::Event::GetEntity);
        auto handleUpdate = std::bind(&RType::Client::RTypeClient::updateEntity, this, std::placeholders::_1);
        refHandlerUpdate.subscribe(handleUpdate);
    }
} // namespace RType::Client
