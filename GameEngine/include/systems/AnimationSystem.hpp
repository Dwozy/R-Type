/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_
#include "GameEngine.hpp"
#include "Registry.hpp"

namespace GameEngine
{
    /// @brief Class representing the sprite sheet animation system
    class AnimationSystem
    {
      public:
        /// @brief constructor
        /// @param deltaTime The delta time of the game for handle game animation
        AnimationSystem(const float &deltaTime) : _deltaTime(deltaTime){};
        /// @brief destructor
        ~AnimationSystem() = default;
        /// @brief overload of () operator function that updates the texture to the next animation
        /// @param texture the Array that contains the texture components
        void operator()(SparseArray<TextureComponent> &texture);

      private:
        const float &_deltaTime;
    };
} // namespace GameEngine

#endif /* !ANIMATIONSYSTEM_HPP_ */
