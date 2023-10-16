/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
#define SCENEMANAGER_HPP_
#include <memory>
#include <string>
#include <unordered_map>
#include "utils/IScene.hpp"

namespace GameEngine
{
    class SceneManager
    {
      public:
        SceneManager(){};
        ~SceneManager() = default;

        void registerScene(const std::string &name, std::unique_ptr<IScene> &&scene);
        void unregisterScene(const std::string &name);

        void loadScene(const std::string &name);
        void unloadScene();

      private:
        std::unordered_map<std::string, std::unique_ptr<IScene>> _scenes;
        std::string _currentScene;
    };
} // namespace GameEngine

#endif /* !SCENEMANAGER_HPP_ */
