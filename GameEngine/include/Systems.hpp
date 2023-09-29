/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
    #define SYSTEMS_HPP_
    #include "Registry.hpp"
    #include <SFML/Graphics.hpp>

namespace GameEngine {
    void SystemLoadingMusic(Registry &r);
    void SystemLoadingText(Registry &r);
    void SystemLoadingTexture(Registry &r);
    void SystemDraw(Registry &r, sf::RenderWindow &window);
}

#endif /* !SYSTEMS_HPP_ */
