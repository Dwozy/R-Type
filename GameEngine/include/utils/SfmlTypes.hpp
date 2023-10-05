/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SfmlTypes
*/

#ifndef SFMLTYPES_HPP_
    #define SFMLTYPES_HPP_
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include "utils/Vector.hpp"
    #include "RenderInterfaces.hpp"

    // maybe remove sftype from function parameter and only take our class
namespace GameEngine
{
    using EventType = std::size_t;

    enum class EventT: EventType
    {
        WindowCloseEvent = 0,
        Resized,
        LostFocus,
        GainedFocus,
        TextEntered,
        KeyPressed,
        KeyReleased,
        MouseWheelMoved,
        MouseWheelScrolled,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseEntered,
        MouseLeft,
        JoystickButtonPressed,
        JoystickButtonReleased,
        JoystickMoved,
        JoystickConnected,
        JoystickDisconnected,
        TouchBegan,
        TouchMoved,
        TouchEnded,
        SensorChanged,
    };

    class Event: public IEvent<sf::Event>
    {
        public:
            sf::Event &getEvent() override {
                return _event;
            }
            sf::Event::EventType &type = _event.type;
            EventT EvenType;
        private:
            sf::Event _event;
    };

    template <typename T>
    class Rect : public IRect<T, sf::Rect>
    {
        public:
            Rect(T left, T top, T width, T height) { _rect = sf::Rect{ left, top, width, height }; };
            ~Rect() = default;
            T &left = _rect.left;
            T &top = _rect.top;
            T &width = _rect.width;
            T &height = _rect.height;

            const sf::Rect<T> &getBaseRect() const override { return _rect; }
        private:
            sf::Rect<T> _rect;
    };

    class Texture : public ITexture<sf::Texture, sf::Rect>
    {
        public:
            Texture() {};
            ~Texture() = default;
            const sf::Texture &getTexture() const override
            {
                return _texture;
            };
            void load(const std::string &filename, const IRect<int, sf::Rect> &area) override
            {
                // add check error here
                _texture.loadFromFile(filename, area.getBaseRect());
            }
        private:
            sf::Texture _texture;
    };

    class View : public IView<sf::View>
    {
        public:
            View(const Rect<float> &rect): _view{sf::Rect<float>{rect.left, rect.top, rect.width, rect.height}} {};
            ~View() = default;
            const sf::View &getBaseView() const override { return _view; }
        private:
            sf::View _view;
    };

    class Window : public IWindow<sf::RenderWindow, sf::View, sf::Event>
    {
        public:
            Window(int width = 1920, int height = 1080, const std::string &title = "Game window")
                : _window(sf::VideoMode(width, height), title), _title(title) {}
            const sf::RenderWindow &getWindow() const override
            {
                return _window;
            }
            void draw(const sf::Drawable &drawable) override
            {
                _window.draw(drawable);
            }
            void setView(const IView<sf::View> &view) override
            {
                _window.setView(view.getBaseView());
            };
            bool isOpen() const override
            {
                return _window.isOpen();
            }
            bool pollEvent(IEvent<sf::Event> &event) override
            {
                return _window.pollEvent(event.getEvent());
            }
            void close() override
            {
                _window.close();
            }
            void display() override
            {
                _window.display();
            };
            void clear() override
            {
                _window.clear();
            };
            void create(int width, int height, const std::string &title) override
            {
                _window.create(sf::VideoMode(width, height), title);
                _title = title;
            }
        private:
            sf::RenderWindow _window;
            std::string _title;
    };

    class Text
    {
         public:
            Text() {};
            ~Text() = default;
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

    class Music
    {
        public:
            Music() {}
            ~Music() = default;
            // Music(const Music &other) {
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

    class Font : public IFont<sf::Font>
    {
        public:
            Font() {};
            ~Font() = default;
            const sf::Font &getFont() const override {
                return _font;
            };
            void load(const std::string &filename) override {
                _font.loadFromFile(filename);
            }
        private:
            sf::Font _font;
    };
    class Sprite : public ISprite<sf::Sprite, sf::Texture, sf::Rect>
    {
        public:
            Sprite() {};
            const sf::Sprite &getSprite() const override
            {
                return _sprite;
            };
            void load(const ITexture<sf::Texture, sf::Rect> &texture, bool resetRect = false) override
            {
                //check if texture loaded befor the set
                _sprite.setTexture(texture.getTexture(), resetRect);
            };
            void setPosition(const Vector2<float> position) override
            {
                _sprite.setPosition(sf::Vector2f{ position.x, position.y });
            };
        private:
            sf::Sprite _sprite;
    };
}
#endif /* !MLTYPES_HPP_ */
