/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Entity
*/

#include "Entity.hpp"

GameEngine::EntityManager::EntityManager()
{
    for (Entity entity = 0; entity < MAX_ENTITY; entity++)
        _entitiesAvailable.push(entity);
}

GameEngine::Entity GameEngine::EntityManager::createEntity()
{
    Entity entity;

    if (_entitiesAvailable.empty())
        throw Error::NoEntityAvailableError();
    entity = _entitiesAvailable.front();
    _entitiesAvailable.pop();
    return entity;
}

void GameEngine::EntityManager::destroyEntity(Entity entity)
{
    if (entity >= MAX_ENTITY)
        throw Error::OutOfEntitiesLimitError();

    _entitiesSignatures[entity].reset();
    _entitiesAvailable.push(entity);
}

void GameEngine::EntityManager::setSignature(Entity entity, Signature signature)
{
    if (entity >= MAX_ENTITY)
        throw Error::OutOfEntitiesLimitError();

    _entitiesSignatures[entity] = signature;
}

GameEngine::Signature GameEngine::EntityManager::getSignature(Entity entity)
{
    if (entity >= MAX_ENTITY)
        throw Error::OutOfEntitiesLimitError();

    return _entitiesSignatures[entity];
}
