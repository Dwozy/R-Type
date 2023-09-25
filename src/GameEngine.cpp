/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameEngine
*/

#include "GameEngine.hpp"

void GameEngine::GameEngine::destroyEntity(Entity entity)
{
    _entityManager->destroyEntity(entity);
    _componentManager->entityDestroyed(entity);
    _systemManager.entityDestroyed(entity);
}
