/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** WinLoseScene
*/

#include "scenes/WinLoseScene.hpp"
#include <iostream>

void WinLoseScene::load() { std::cout << "Loading WinLoseScene" << std::endl; }

void WinLoseScene::unload() { std::cout << "Unloading WinLoseScene" << std::endl; }

void WinLoseScene::addEntityToUnload(GameEngine::Entity) {}
