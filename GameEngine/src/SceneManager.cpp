/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneManager
*/

#include "SceneManager.hpp"

namespace GameEngine
{
    void SceneManager::registerScene(const std::string &name, std::unique_ptr<IScene> &&scene)
    {
        if (name == "")
            throw; // Invalid scene name
        _scenes.insert({name, std::move(scene)});
    }
    void SceneManager::unregisterScene(const std::string &name)
    {
        if (_scenes.find(name) == _scenes.end())
            throw; // scene not registered
        _scenes.erase(name);
    }

    void SceneManager::loadScene(const std::string &name)
    {
        if (_scenes.find(name) == _scenes.end())
            throw; // scene not registered
        _currentScene = name;
        _scenes[name]->load();
    }
    void SceneManager::unloadScene()
    {
        if (_scenes.find(_currentScene) == _scenes.end())
            return;
        _scenes[_currentScene]->unload();
        _currentScene = "";
    }
} // namespace GameEngine
