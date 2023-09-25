/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sfmlTypes
*/

#ifndef SFMLTYPES_HPP_
    #define SFMLTYPES_HPP_
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>

namespace GameEngine {
    class Music
    {
        public:
            Music();
            ~Music() = default;
        private:
            sf::Music _music;
    };
    class Text {
         public:
            Text();
            ~Text() = default;
        private:
            sf::Text _text;
    };
    class Font {
        public:
            Font();
            ~Font() = default;
        private:
            sf::Font _font;
    };
    class Texture {
        public:
            Texture();
            ~Texture() = default;
        private:
            sf::Texture _texture;
    };
    class View {
        public:
            View();
            ~View() = default;
        private:
            sf::View _View;
    };
    class Sprite {
        public:
            Sprite();
            ~Sprite() = default;
        private:
            sf::Sprite _sprite;
    };
}
#endif /* !SFMLTYPES_HPP_ */
