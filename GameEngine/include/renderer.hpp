/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** rendere
*/

#ifndef RENDERE_HPP_
    #define RENDERE_HPP_
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <string>

    namespace GameEngine {
        class RendererManager
        {
            public:
                RendererManager(unsigned int Width, unsigned int Height, std::string WindowTitle);
                ~RendererManager() = default;
                sf::RenderWindow &getWindow();
                sf::Event &getEvent();
            private:
                sf::RenderWindow _window;
                sf::Event _event;
        };
    }

#endif /* !RENDERE_HPP_ */
