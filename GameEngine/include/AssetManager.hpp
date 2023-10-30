/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** AssetManager
*/

#ifndef AssetManager_HPP_
#define AssetManager_HPP_
#include <unordered_map>
#include <iostream>
#include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    /// @brief Class to manage assets
    class AssetManager
    {
      public:
        /// @brief Default constructor
        AssetManager() = default;
        /// @brief Default destructor
        ~AssetManager() = default;
        /// @brief Load a texture from a file
        /// @param filename name of the file
        /// @param area area of the texture
        void loadTexture(const std::string &filename, Recti area)
        {
            _texture[filename] = Texture();
            _texture[filename].load(filename, area);
        }

        /// @brief Get a texture previously loaded
        /// @param textureName name of the texture
        /// @return const reference to the texture
        const Texture &getTexture(const std::string &textureName) const { return _texture.at(textureName); }

      protected:
      private:
        std::unordered_map<std::string, Texture> _texture;
    };
} // namespace GameEngine

#endif /* !AssetManager_HPP_ */
