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
            SFMusic() {};
            ~SFMusic() = default;
            const sf::Music &getMusic() const {
                return _music;
            }

        private:
            sf::Music _music;
    };
    class SFWindow {
        public:
            SFWindow() {};
            ~SFWindow() = default;
            const sf::RenderWindow &getWindow() const {
                return _window;
            }
        private:
            sf::RenderWindow _window;
    };
    class SFText {
         public:
            SFText() {};
            ~SFText() = default;
            const sf::Text &getText() const {
                return _text;
            }
            void load(const std::string &text,const sf::Font &font, size_t size){
                _text.setString(text);
                _text.setFont(font);
                _text.setCharacterSize(size);
            }
        private:
            sf::Text _text;
    };
    class SFFont {
        public:
            SFFont() {};
            ~SFFont() = default;
            const sf::Font &getFont() const {
                return _font;
            };
            void load(const std::string &filename) {
                _font.loadFromFile(filename);
            }
        private:
            sf::Font _font;
    };
    class SFTexture {
        public:
            SFTexture() {};
            ~SFTexture() = default;
            const sf::Texture &getTexture() const {
                return _texture;
            }
            void load(std::string filename) {
                // add check error here
                _texture.loadFromFile(filename);
            }
        private:
            sf::Texture _texture;
    };
    class SFView {
        public:
            SFView() {};
            ~SFView() = default;
            const sf::View &getView() const  {
                return _view;
            };
        private:
            sf::View _view;
    };
    class SFSprite {
        public:
            SFSprite() {};
            ~SFSprite() = default;
            const sf::Sprite &getSprite() const {
                return _sprite;
            };
            void load(const sf::Texture &texture, bool resetRect=false) {
                //check if texture loaded befor the set
                _sprite.setTexture(texture, resetRect);
            }
        private:
            sf::Sprite _sprite;
    };
}
#endif /* !SFMLTYPES_HPP_ */
