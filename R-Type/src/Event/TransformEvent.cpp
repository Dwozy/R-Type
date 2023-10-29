/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ShootEvent
*/

#include "RTypeClient.hpp"
#include "components/NetworkIdComponent.hpp"

namespace RType::Client
{
    void RTypeClient::getTransformInformation(struct RType::Protocol::TransformData transformData)
    {
        auto &transforms = _gameEngine.registry.getComponent<GameEngine::TransformComponent>();
        std::size_t id = 0;

        if (!_searchEntity(transformData.id)) {
            GameEngine::Entity entity = _gameEngine.registry.spawnEntity();
            _gameEngine.registry.addComponent<GameEngine::NetworkIdComponent>(
                entity, GameEngine::NetworkIdComponent{transformData.id});
            GameEngine::TransformComponent tsf = {GameEngine::Vector2<float>(transformData.x, transformData.y),
                GameEngine::Vector2<float>(transformData.dx, transformData.dy)};
            _gameEngine.registry.addComponent<GameEngine::TransformComponent>(entity, tsf);
        }
        id = _findEntity(transformData.id);
        if (!transforms[id]) {
            GameEngine::Entity entity = _gameEngine.registry.getEntityById(id);
            GameEngine::TransformComponent tsf = {GameEngine::Vector2<float>(transformData.x, transformData.y),
                GameEngine::Vector2<float>(transformData.dx, transformData.dy)};
            _gameEngine.registry.addComponent<GameEngine::TransformComponent>(entity, tsf);
        } else {
            transforms[id]->position.x = (fabs(transforms[id]->position.x - transformData.x) < 2)
                                             ? transforms[id]->position.x
                                             : transformData.x;
            transforms[id]->position.y = (fabs(transforms[id]->position.y - transformData.y) < 2)
                                             ? transforms[id]->position.y
                                             : transformData.y;
            transforms[id]->velocity.x = transformData.dx;
            transforms[id]->velocity.y = transformData.dy;
        }
    }

    void RTypeClient::setTransformCallback()
    {
        auto &refHandleTransform =
            _gameEngine.eventManager.addHandler<struct RType::Protocol::TransformData>(GameEngine::Event::GetTransform);
        auto handleGetTransform =
            std::bind(&RType::Client::RTypeClient::getTransformInformation, this, std::placeholders::_1);
        refHandleTransform.subscribe(handleGetTransform);
    }
} // namespace RType::Client
