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
    class AssetManager
    {
      public:
        AssetManager() = default;
        ~AssetManager() = default;
        void loadTexture(const std::string &filename, Recti area)
        {
            if (_texture.find(filename) == _texture.end()) {
                _texture[filename] = Texture();
                _texture[filename].load(filename, area);
            }
        }

        const Texture &getTexture(const std::string &textureName) const { return _texture.at(textureName); }

      protected:
      private:
        std::unordered_map<std::string, Texture> _texture;
    };
} // namespace GameEngine

#endif /* !AssetManager_HPP_ */
