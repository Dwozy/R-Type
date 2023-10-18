/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimeSystem
*/

#ifndef ANIMESYSTEM_HPP_
#define ANIMESYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"

namespace GameEngine
{
    /// @brief Class representing the sprite sheet animation system
    class AnimeSystem
    {
      public:
        /// @brief constructor
        /// @param deltaTime The delta time of the game for handle game animation
        AnimeSystem(const float &deltaTime) : _deltaTime(deltaTime), _currentDeltaTime(0.0f){};
        /// @brief destructor
        ~AnimeSystem() = default;
        /// @brief overload of () operator function that updates the texture to the next animation
        /// @param texture the Array that contains the texture components
        void operator()(SparseArray<TextureComponent> &texture);

      private:
        const float &_deltaTime;
        float _currentDeltaTime;
    };
} // namespace GameEngine

#endif /* !ANIMESYSTEM_HPP_ */
