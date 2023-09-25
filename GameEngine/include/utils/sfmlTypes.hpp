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
    class SFMusic
    {
        public:
            SFMusic();
            ~SFMusic() = default;
        private:
            sf::Music _music;
    };
    class SFText {
         public:
            SFText();
            ~SFText() = default;
        private:
            sf::Text _text;
    };
    class SFFont {
        public:
            SFFont();
            ~SFFont() = default;
        private:
            sf::Font _font;
    };
    class SFTexture {
        public:
            SFTexture();
            ~SFTexture() = default;
        private:
            sf::Texture _texture;
    };
    class SFView {
        public:
            SFView();
            ~SFView() = default;
        private:
            sf::View _View;
    };
    class SFSprite {
        public:
            SFSprite();
            ~SFSprite() = default;
        private:
            sf::Sprite _sprite;
    };
}
#endif /* !SFMLTYPES_HPP_ */
