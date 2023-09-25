/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SafeEntity
*/

#include "utils/SafeEntity.hpp"

GameEngine::SafeEntity::SafeEntity(GameEngine &gameEngine): _gameEngine(gameEngine)
{
    _entity = _gameEngine.createEntity();
}

GameEngine::SafeEntity::~SafeEntity()
{
    _gameEngine.destroyEntity(_entity);
}
