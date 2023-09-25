/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EntityManager
*/

#include "Entity.hpp"

GameEngine::EntityManager::EntityManager(Entity maxEntities): _maxEntities(maxEntities)
{
    _entitiesAvailable.reserve(maxEntities);
    _entitiesSignatures.reserve(maxEntities);
    for (Entity entity = 0; entity < _maxEntities; entity++)
        _entitiesAvailable.push_back(entity);
}

GameEngine::Entity GameEngine::EntityManager::createEntity()
{
    Entity entity;

    if (_entitiesAvailable.empty())
        throw Error::NoEntityAvailableError();
    entity = _entitiesAvailable.front();
    _entitiesAvailable.erase(_entitiesAvailable.begin());
    return entity;
}

void GameEngine::EntityManager::destroyEntity(Entity entity)
{
    if (entity >= _maxEntities)
        throw Error::OutOfEntitiesLimitError();

    _entitiesSignatures[entity].reset();
    _entitiesAvailable.push_back(entity);
}

void GameEngine::EntityManager::setSignature(Entity entity, Signature signature)
{
    if (entity >= _maxEntities)
        throw Error::OutOfEntitiesLimitError();

    _entitiesSignatures[entity] = signature;
}

const GameEngine::Signature &GameEngine::EntityManager::getSignature(Entity entity) const
{
    if (entity >= _maxEntities)
        throw Error::OutOfEntitiesLimitError();

    return _entitiesSignatures[entity];
};
