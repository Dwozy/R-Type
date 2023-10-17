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
#include "utils/Rect.hpp"
#include "RenderInterfaces.hpp"
#include "Keyboard.hpp"

// maybe remove sftype from function parameter and only take our class
namespace GameEngine
{
    using EventType = std::size_t;

    enum class EventT : EventType {
        WindowCloseEvent = 0,
        Resized,
        LostFocus,
        GainedFocus,
        TextEntered,
        KeyPressed,
        KeyReleased,
        MouseWheelScrolled,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseEntered,
        MouseLeft,
    };

    class SEvent : public IEvent<sf::Event>
    {
      public:
        sf::Event &getEvent() override { return _event; }
        sf::Event::EventType &type = _event.type;
        EventT EvenType;

      private:
        sf::Event _event;
    };

    class Texture : public ITexture<sf::Texture, sf::Rect>
    {
      public:
        Texture(){};
        ~Texture() = default;
        const sf::Texture &getTexture() const override { return _texture; };
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
        View(const Rect<float> &rect) : _view{sf::Rect<float>{rect.left, rect.top, rect.width, rect.height}} {};
        ~View() = default;
        const sf::View &getBaseView() const override { return _view; }

      private:
        sf::View _view;
    };

    class Window : public IWindow<sf::RenderWindow, sf::View, sf::Event, sf::Drawable>
    {
      public:
        Window(int width = 1920, int height = 1080, const std::string &title = "Game window")
            : _window(sf::VideoMode(width, height), title), _title(title)
        {
        }
        const sf::RenderWindow &getWindow() const override { return _window; }
        void draw(const sf::Drawable &drawable) override { _window.draw(drawable); }
        void setView(const IView<sf::View> &view) override { _window.setView(view.getBaseView()); };
        bool isOpen() const override { return _window.isOpen(); }
        bool pollEvent(IEvent<sf::Event> &event) override { return _window.pollEvent(event.getEvent()); }
        void close() override { _window.close(); }
        void display() override { _window.display(); };
        void clear() override { _window.clear(); };
        void create(int width, int height, const std::string &title) override
        {
            _window.create(sf::VideoMode(width, height), title);
            _title = title;
        }
        Vector2<float> mapPixelToCoords(const Vector2<int> &pos)
        {
            sf::Vector2f coord = _window.mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
            return Vector2<float>(coord.x, coord.y);
        };

      private:
        sf::RenderWindow _window;
        std::string _title;
    };

    class Text
    {
      public:
        Text(){};
        ~Text() = default;
        const sf::Text &getText() const { return _text; }
        void load(const std::string &text, const sf::Font &font, size_t size)
        {
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
        const sf::Music &getMusic() const { return _music; }
        void load(const std::string &filename)
        {
            _music.openFromFile(filename);
            _filename = filename;
        }
        const std::string &getFilename() const { return _filename; }

      private:
        sf::Music _music;
        std::string _filename;
    };

    class Font : public IFont<sf::Font>
    {
      public:
        Font(){};
        ~Font() = default;
        const sf::Font &getFont() const override { return _font; };
        void load(const std::string &filename) override { _font.loadFromFile(filename); }

      private:
        sf::Font _font;
    };
    class Sprite : public ISprite<sf::Sprite, sf::Texture, sf::Rect>
    {
      public:
        Sprite(){};
        const sf::Sprite &getSprite() const override { return _sprite; };
        void load(const ITexture<sf::Texture, sf::Rect> &texture, bool resetRect = false) override
        {
            _sprite.setTexture(texture.getTexture(), resetRect);
        };
        void setPosition(const Vector2<float> position) override
        {
            _sprite.setPosition(sf::Vector2f{position.x, position.y});
        };
        void setTextureRect(const IRect<int, sf::Rect> &newRect) override
        {
            _sprite.setTextureRect(newRect.getBaseRect());
        };
        void setRect(const Recti &rect) { _sprite.setTextureRect(rect.getBaseRect()); };
        void setScale(const float &x, const float &y) { _sprite.setScale(x, y); };

      private:
        sf::Sprite _sprite;
    };

    static const std::unordered_map<Input::Keyboard::Key, sf::Keyboard::Key> sfKeys = {
        {Input::Keyboard::Key::NO_KEY, sf::Keyboard::Unknown}, {Input::Keyboard::Key::A, sf::Keyboard::A},
        {Input::Keyboard::Key::B, sf::Keyboard::B}, {Input::Keyboard::Key::C, sf::Keyboard::C},
        {Input::Keyboard::Key::D, sf::Keyboard::D}, {Input::Keyboard::Key::E, sf::Keyboard::E},
        {Input::Keyboard::Key::F, sf::Keyboard::F}, {Input::Keyboard::Key::G, sf::Keyboard::G},
        {Input::Keyboard::Key::H, sf::Keyboard::H}, {Input::Keyboard::Key::I, sf::Keyboard::I},
        {Input::Keyboard::Key::J, sf::Keyboard::J}, {Input::Keyboard::Key::K, sf::Keyboard::K},
        {Input::Keyboard::Key::L, sf::Keyboard::L}, {Input::Keyboard::Key::M, sf::Keyboard::M},
        {Input::Keyboard::Key::N, sf::Keyboard::N}, {Input::Keyboard::Key::O, sf::Keyboard::O},
        {Input::Keyboard::Key::P, sf::Keyboard::P}, {Input::Keyboard::Key::Q, sf::Keyboard::Q},
        {Input::Keyboard::Key::R, sf::Keyboard::R}, {Input::Keyboard::Key::S, sf::Keyboard::S},
        {Input::Keyboard::Key::T, sf::Keyboard::T}, {Input::Keyboard::Key::U, sf::Keyboard::U},
        {Input::Keyboard::Key::V, sf::Keyboard::V}, {Input::Keyboard::Key::W, sf::Keyboard::W},
        {Input::Keyboard::Key::X, sf::Keyboard::X}, {Input::Keyboard::Key::Y, sf::Keyboard::Y},
        {Input::Keyboard::Key::Z, sf::Keyboard::Z}, {Input::Keyboard::Key::Num0, sf::Keyboard::Num0},
        {Input::Keyboard::Key::Num1, sf::Keyboard::Num1}, {Input::Keyboard::Key::Num2, sf::Keyboard::Num2},
        {Input::Keyboard::Key::Num3, sf::Keyboard::Num3}, {Input::Keyboard::Key::Num4, sf::Keyboard::Num4},
        {Input::Keyboard::Key::Num5, sf::Keyboard::Num5}, {Input::Keyboard::Key::Num6, sf::Keyboard::Num6},
        {Input::Keyboard::Key::Num7, sf::Keyboard::Num7}, {Input::Keyboard::Key::Num8, sf::Keyboard::Num8},
        {Input::Keyboard::Key::Num9, sf::Keyboard::Num9}, {Input::Keyboard::Key::Escape, sf::Keyboard::Escape},
        {Input::Keyboard::Key::LControl, sf::Keyboard::LControl}, {Input::Keyboard::Key::LShift, sf::Keyboard::LShift},
        {Input::Keyboard::Key::LAlt, sf::Keyboard::LAlt}, {Input::Keyboard::Key::LSystem, sf::Keyboard::LSystem},
        {Input::Keyboard::Key::RControl, sf::Keyboard::RControl}, {Input::Keyboard::Key::RShift, sf::Keyboard::RShift},
        {Input::Keyboard::Key::RAlt, sf::Keyboard::RAlt}, {Input::Keyboard::Key::RSystem, sf::Keyboard::RSystem},
        {Input::Keyboard::Key::Menu, sf::Keyboard::Menu}, {Input::Keyboard::Key::LBracket, sf::Keyboard::LBracket},
        {Input::Keyboard::Key::RBracket, sf::Keyboard::RBracket},
        {Input::Keyboard::Key::Semicolon, sf::Keyboard::Semicolon}, {Input::Keyboard::Key::Comma, sf::Keyboard::Comma},
        {Input::Keyboard::Key::Period, sf::Keyboard::Period}, {Input::Keyboard::Key::Quote, sf::Keyboard::Quote},
        {Input::Keyboard::Key::Slash, sf::Keyboard::Slash}, {Input::Keyboard::Key::Backslash, sf::Keyboard::Backslash},
        {Input::Keyboard::Key::Tilde, sf::Keyboard::Tilde}, {Input::Keyboard::Key::Equal, sf::Keyboard::Equal},
        {Input::Keyboard::Key::Dash, sf::Keyboard::Dash}, {Input::Keyboard::Key::Space, sf::Keyboard::Space},
        {Input::Keyboard::Key::Enter, sf::Keyboard::Enter}, {Input::Keyboard::Key::Backspace, sf::Keyboard::Backspace},
        {Input::Keyboard::Key::Tab, sf::Keyboard::Tab}, {Input::Keyboard::Key::Add, sf::Keyboard::Add},
        {Input::Keyboard::Key::Subtract, sf::Keyboard::Subtract},
        {Input::Keyboard::Key::Multiply, sf::Keyboard::Multiply}, {Input::Keyboard::Key::Divide, sf::Keyboard::Divide},
        {Input::Keyboard::Key::Left, sf::Keyboard::Left}, {Input::Keyboard::Key::Right, sf::Keyboard::Right},
        {Input::Keyboard::Key::Up, sf::Keyboard::Up}, {Input::Keyboard::Key::Down, sf::Keyboard::Down},
        {Input::Keyboard::Key::Numpad0, sf::Keyboard::Numpad0}, {Input::Keyboard::Key::Numpad1, sf::Keyboard::Numpad1},
        {Input::Keyboard::Key::Numpad2, sf::Keyboard::Numpad2}, {Input::Keyboard::Key::Numpad3, sf::Keyboard::Numpad3},
        {Input::Keyboard::Key::Numpad4, sf::Keyboard::Numpad4}, {Input::Keyboard::Key::Numpad5, sf::Keyboard::Numpad5},
        {Input::Keyboard::Key::Numpad6, sf::Keyboard::Numpad6}, {Input::Keyboard::Key::Numpad7, sf::Keyboard::Numpad7},
        {Input::Keyboard::Key::Numpad8, sf::Keyboard::Numpad8}, {Input::Keyboard::Key::Numpad9, sf::Keyboard::Numpad9},
        {Input::Keyboard::Key::F1, sf::Keyboard::F1}, {Input::Keyboard::Key::F2, sf::Keyboard::F2},
        {Input::Keyboard::Key::F3, sf::Keyboard::F3}, {Input::Keyboard::Key::F4, sf::Keyboard::F4},
        {Input::Keyboard::Key::F5, sf::Keyboard::F5}, {Input::Keyboard::Key::F6, sf::Keyboard::F6},
        {Input::Keyboard::Key::F7, sf::Keyboard::F7}, {Input::Keyboard::Key::F8, sf::Keyboard::F8},
        {Input::Keyboard::Key::F9, sf::Keyboard::F9}, {Input::Keyboard::Key::F10, sf::Keyboard::F10},
        {Input::Keyboard::Key::F11, sf::Keyboard::F11}, {Input::Keyboard::Key::F12, sf::Keyboard::F12},
        {Input::Keyboard::Key::F13, sf::Keyboard::F13}, {Input::Keyboard::Key::F14, sf::Keyboard::F14},
        {Input::Keyboard::Key::F15, sf::Keyboard::F15}, {Input::Keyboard::Key::Pause, sf::Keyboard::Pause}};

    static bool isKeyPressed(const Input::Keyboard::Key key) { return sf::Keyboard::isKeyPressed(sfKeys.at(key)); }

} // namespace GameEngine
#endif /* !MLTYPES_HPP_ */
