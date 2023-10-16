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
    /// @brief Class managing all the scenes for the game.
    class SceneManager
    {
      public:
        /// @brief Default constructor
        SceneManager(){};
        /// @brief Default destructor
        ~SceneManager() = default;

        /// @brief Registers a new scene.
        /// @param name Name of the scene to register. Will be used when loading the scene.
        /// @param scene Unique pointer to the scene class to register. The scene will be moved in the SceneManager.
        void registerScene(const std::string &name, std::unique_ptr<IScene> &&scene);
        /// @brief Unregisters a scene.
        /// @param name Name of the scene to unregister.
        void unregisterScene(const std::string &name);

        /// @brief Loads a scene. Previous scene needs to be unregister before or the scenes will overlap.
        /// @param name Name of the scene to load.
        void loadScene(const std::string &name);
        /// @brief Unloads the currently loaded scene.
        void unloadScene();

      private:
        std::unordered_map<std::string, std::unique_ptr<IScene>> _scenes;
        std::string _currentScene;
    };
} // namespace GameEngine

#endif /* !SCENEMANAGER_HPP_ */
