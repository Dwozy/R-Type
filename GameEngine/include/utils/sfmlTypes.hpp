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
    #include "utils/Rect.hpp"

    // maybe remove sftype from function parameter and only take our class
namespace GameEngine
{
    class SFWindow {
        public:
            SFWindow(int width = 1920, int height = 1080, const std::string &title = "Game window")
                : _window(sf::VideoMode(width, height), title), _title(title) {}
            // SFWindow(const SFWindow &other)
            //     : _window(sf::VideoMode(other._window.getSize().x, other._window.getSize().y), other._title), _title(other._title) {}
            ~SFWindow() = default;
            const sf::RenderWindow &getWindow() const {
                return _window;
            }
            void draw(const sf::Drawable &drawable) {
                _window.draw(drawable);
            }
            void create(int width, int height, const std::string &title) {
                _window.create(sf::VideoMode(width, height), title);
                _title = title;
            }
        private:
            sf::RenderWindow _window;
            std::string _title;
        };
    class SFText
    {
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
    class SFMusic {
        public:
            SFMusic() {}
            ~SFMusic() = default;
            // SFMusic(const SFMusic &other) {
            //     if (!other.getFilename().empty()) {
            //         load(other.getFilename());
            //     }
            // }
            const sf::Music &getMusic() const {
                return _music;
            }
            void load(const std::string &filename) {
                _music.openFromFile(filename);
                _filename = filename;
            }
            const std::string &getFilename() const {
                return _filename;
            }
        private:
            sf::Music _music;
            std::string _filename;
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
            const sf::Texture &getTexture() const
            {
                return _texture;
            }
            void load(const std::string &filename, const Rect<int> &area)
            {
                // add check error here
                _texture.loadFromFile(filename, area.getBaseRect());
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
            void load(const SFTexture &texture, bool resetRect = false)
            {
                //check if texture loaded befor the set
                _sprite.setTexture(texture.getTexture(), resetRect);
            };
            void setPosition(const Vector2<float> position)
            {
                _sprite.setPosition(sf::Vector2f{ position.x, position.y });
            };
        private:
            sf::Sprite _sprite;
    };
}
#endif /* !SFMLTYPES_HPP_ */
