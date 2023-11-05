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
#include "unordered_map"
#include "RenderInterfaces.hpp"
#include "Keyboard.hpp"

#ifdef DEBUG
    #include "Debug.hpp"
    #include <imgui.h>
    #include <imgui-SFML.h>
    #include "Error.hpp"
#endif

namespace GameEngine
{
    /// @brief Class representing a custom event wrapper for sf::Event
    class SEvent : public IEvent<sf::Event>
    {
      public:
        /// @brief Default constructor for SEvent
        SEvent() = default;
        /// @brief Returns the wrapped sf::Event
        /// @return Reference to the sf::Event instance
        sf::Event &getEvent() override { return _event; }
        /// @brief Reference to the EventType of the wrapped sf::Event
        sf::Event::EventType &type = _event.type;

      private:
        sf::Event _event;
    };

    class Clock : public IClock<sf::Clock>
    {
      public:
        /// @brief Default constructor for Clock
        Clock() = default;
        /// @brief Returns the wrapped sf::Clock
        /// @return Reference to the sf::Clock instance
        sf::Clock &getClock() override { return _clock; }

      private:
        sf::Clock _clock;
    };

    /// @brief Class representing a texture wrapper for sf::Texture with an associated area
    class Texture : public ITexture<sf::Texture, sf::Rect>
    {
      public:
        /// @brief Default constructor for Texture
        Texture() = default;
        /// @brief Destructor for Texture
        ~Texture() = default;
        /// @brief Returns the wrapped sf::Texture
        /// @return Reference to the sf::Texture instance
        const sf::Texture &getTexture() const override { return _texture; };
        /// @brief Loads a texture from a file with a specified area
        /// @param filename The path to the texture file
        /// @param area The area of the texture to load
        void load(const std::string &filename, const IRect<int, sf::Rect> &area) override
        {
            _texture.loadFromFile(filename, area.getBaseRect());
        }

      private:
        sf::Texture _texture;
    };

    /// @brief Class representing a view wrapper for sf::View
    class View : public IView<sf::View>
    {
      public:
        /// @brief default constructor
        View() = default;
        /// @brief Constructor for View
        /// @param rect The rectangle defining the initial position and size of the view
        View(const Rect<float> &rect) : _view{sf::Rect<float>{rect.left, rect.top, rect.width, rect.height}} {};
        /// @brief Destructor for View
        ~View() = default;
        /// @brief Returns the wrapped sf::View
        /// @return Reference to the sf::View instance
        const sf::View &getBaseView() const override { return _view; }
        /// @brief set center of the view
        /// @param center point to center the view
        void setCenter(const Vector2<float> &center) override { _view.setCenter(center.x, center.y); }
        /// @brief get the center of the view
        /// @return the center of the view
        Vector2<float> getCenter() const override
        {
            auto center = _view.getCenter();
            return Vector2<float>{center.x, center.y};
        }
        /// @brief set a viewport rectangle
        /// @param startingPoint the point at the up left corner of the viewport rectangle
        /// @param width the width of the viewport
        /// @param height the height of the viewport
        void setViewPort(const Vector2<float> &startingPoint, float width, float height) override
        {
            _view.setViewport(sf::FloatRect{startingPoint.x, startingPoint.y, width, height});
        }

      private:
        sf::View _view;
    };

    /// @brief Class representing a window wrapper for sf::RenderWindow with additional functionality
    class Window : public IWindow<sf::RenderWindow, sf::View, sf::Event, sf::Drawable>
    {
      public:
        /// @brief Constructor for Window
#ifdef DEBUG
/// @param debugMenu reference to the debug menu
#endif
        /// @param width The width of the window
        /// @param height The height of the window
        /// @param title The title of the window
#ifdef DEBUG
        Window(
            Debug::DebugMenu &debugMenu, int width = 1920, int height = 1080, const std::string &title = "Game window")
            : _window(sf::VideoMode(width, height), title), _title(title), _debugMenu(debugMenu)
        {
        }
#else
        Window(int width = 1920, int height = 1080, const std::string &title = "Game window")
            : _window(sf::VideoMode(width, height), title), _title(title)
        {
        }
#endif
        /// @brief Returns the wrapped sf::RenderWindow
        /// @return Reference to the sf::RenderWindow instance
        const sf::RenderWindow &getWindow() const override { return _window; }
        /// @brief Returns the wrapped sf::RenderWindow
        /// @return Reference to the sf::RenderWindow instance
        sf::RenderWindow &getWindow() override { return _window; }
        /// @brief Draws a sf::Drawable object on the window
        /// @param drawable The object to be drawn
        void draw(const sf::Drawable &drawable) override { _window.draw(drawable); }
        /// @brief Sets the view of the window
        /// @param view The view to set
        void setView(const IView<sf::View> &view) override { _window.setView(view.getBaseView()); };
        /// @brief Set the maximum framerate of the window
        /// @param rate the maximum framerate
        void setFramerateLimit(const float rate) override { _window.setFramerateLimit(rate); };
        /// @brief Checks if the window is open
        /// @return True if the window is open, false otherwise
        bool isOpen() const override { return _window.isOpen(); }
        /// @brief Polls and retrieves the next event
        /// @param event The event to be filled with the polled event
        /// @return True if an event was polled, false otherwise
        bool pollEvent(IEvent<sf::Event> &event) override
        {
            bool result = _window.pollEvent(event.getEvent());
#ifdef DEBUG
            ImGui::SFML::ProcessEvent(_window, event.getEvent());
#endif
            return result;
        }
        /// @brief Closes the window
        void close() override { _window.close(); }
        /// @brief Displays the contents of the window
        void display() override { _window.display(); };
        /// @brief Clears the contents of the window
        void clear() override { _window.clear(); };
        /// @brief Creates a new window with the specified dimensions and title
        /// @param width The width of the new window
        /// @param height The height of the new window
        /// @param title The title of the new window
        void create(int width, int height, const std::string &title) override
        {
            _window.create(sf::VideoMode(width, height), title);
            _title = title;
        }
        /// @brief Maps pixel coordinates to world coordinates
        /// @param pos The pixel coordinates to map
        /// @return The corresponding world coordinates
        Vector2<float> mapPixelToCoords(const Vector2<int> &pos)
        {
            sf::Vector2f coord = _window.mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
            return Vector2<float>(coord.x, coord.y);
        };

#ifdef DEBUG
        /// @brief initialize the ImGui-SFML context to be able to draw the Debug Menu
        void initDebug() override
        {
            if (!ImGui::SFML::Init(_window))
                throw Error::ImGuiSFMLInitError();
            ImGuiIO &io = ImGui::GetIO();
            io.IniFilename = NULL;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        }
        /// @brief Shutdown the ImGui-SFML context
        void shutdownDebug() override { ImGui::SFML::Shutdown(); }
        /// @brief Update the ImGui-SFML context and draw the Debug Menu
        void drawDebug() override
        {
            ImGui::SFML::Update(_window, _debugClock.getClock().restart());
            _debugMenu.draw();
            ImGui::SFML::Render(_window);
        }
#endif

      private:
        sf::RenderWindow _window;
        std::string _title;
#ifdef DEBUG
        Debug::DebugMenu &_debugMenu;
        Clock _debugClock;
#endif
    };

    /// @brief Class representing a text wrapper for sf::Text with basic functionality
    class Text
    {
      public:
        /// @brief Default constructor for Text
        Text(){};
        /// @brief Destructor for Text
        ~Text() = default;
        /// @brief Returns the wrapped sf::Text
        /// @return Reference to the sf::Text instance
        const sf::Text &getText() const { return _text; }
        /// @brief Loads text with specified font and size
        /// @param text The string to set for the text
        /// @param font The font to apply to the text
        /// @param size The character size of the text
        void load(const std::string &text, const sf::Font &font, size_t size)
        {
            _text.setString(text);
            _text.setFont(font);
            _text.setCharacterSize(size);
        }
        void setPosition(const Vector2<float> &position)
        {
            _text.setPosition(static_cast<int>(position.x), static_cast<int>(position.y));
        }
        void setString(const std::string &string) { _text.setString(string); }

        Rectf getLocalBounds() const
        {
            return Rectf(_text.getLocalBounds().left, _text.getLocalBounds().top, _text.getLocalBounds().width,
                _text.getLocalBounds().height);
        }

      private:
        sf::Text _text;
    };
    /// @brief Class representing a music wrapper for sf::Music
    class Music
    {
      public:
        /// @brief Default constructor for Music
        Music() {}
        /// @brief Destructor for Music
        ~Music() = default;
        /// @brief Returns the wrapped sf::Music
        /// @return Reference to the sf::Music instance
        const sf::Music &getMusic() const { return _music; }
        /// @brief Loads music from a file
        /// @param filename The path to the music file
        void load(const std::string &filename)
        {
            _music.openFromFile(filename);
            _filename = filename;
        }
        /// @brief Returns the filename of the loaded music
        /// @return Reference to the string containing the filename
        const std::string &getFilename() const { return _filename; }

      private:
        sf::Music _music;
        std::string _filename;
    };

    /// @brief Class representing a font wrapper for sf::Font
    class Font : public IFont<sf::Font>
    {
      public:
        /// @brief Default constructor for Font
        Font(){};
        /// @brief Destructor for Font
        ~Font() = default;
        /// @brief Returns the wrapped sf::Font
        /// @return Reference to the sf::Font instance
        const sf::Font &getFont() const override { return _font; };
        /// @brief Loads the font from a file
        /// @param filename The path to the font file
        void load(const std::string &filename) override { _font.loadFromFile(filename); }

      private:
        sf::Font _font;
    };
    /// @brief Class representing a sprite wrapper for sf::Sprite with additional functionality
    class Sprite : public ISprite<sf::Sprite, sf::Texture, sf::Rect>
    {
      public:
        /// @brief Default constructor for Sprite
        Sprite(){};
        /// @brief Destructor for Sprite
        ~Sprite() = default;
        /// @brief Returns the wrapped sf::Sprite
        /// @return Reference to the sf::Sprite instance
        const sf::Sprite &getSprite() const override { return _sprite; };
        /// @brief Loads the sprite with a specified texture and optional reset of the texture rectangle
        /// @param texture The texture to apply to the sprite
        /// @param resetRect Flag indicating whether to reset the texture rectangle
        void load(const ITexture<sf::Texture, sf::Rect> &texture, bool resetRect = false) override
        {
            _sprite.setTexture(texture.getTexture(), resetRect);
        };
        /// @brief Sets the position of the sprite
        /// @param position The new position of the sprite
        void setPosition(const Vector2<float> position) override
        {
            _sprite.setPosition(sf::Vector2f{position.x, position.y});
        };
        /// @brief Sets the texture rectangle of the sprite
        /// @param newRect The new texture rectangle to set
        void setTextureRect(const IRect<int, sf::Rect> &newRect) override
        {
            _sprite.setTextureRect(newRect.getBaseRect());
        };
        /// @brief Sets the texture rectangle of the sprite using a custom rectangle
        /// @param rect The custom rectangle defining the new texture rectangle
        void setRect(const Recti &rect) { _sprite.setTextureRect(rect.getBaseRect()); };
        void setScale(const float &x, const float &y) { _sprite.setScale(x, y); };

      private:
        sf::Sprite _sprite;
    };

    class InputManager
    {
      public:
        /// @brief Static unordered map that maps custom keyboard keys to corresponding sf::Keyboard::Key values
        static const std::unordered_map<Input::Keyboard::Key, sf::Keyboard::Key> sfKeys;

        static bool isKeyPressed(const Input::Keyboard::Key key) { return sf::Keyboard::isKeyPressed(sfKeys.at(key)); }

        static bool isKeyReleased(const Input::Keyboard::Key key)
        {
            bool isReleased = prevKeyStates[key] && sf::Keyboard::isKeyPressed(sfKeys.at(key)) == false;
            prevKeyStates[key] = sf::Keyboard::isKeyPressed(sfKeys.at(key));

            return isReleased;
        }

      private:
        static std::unordered_map<Input::Keyboard::Key, bool> prevKeyStates;
    };
} // namespace GameEngine
#endif /* !MLTYPES_HPP_ */
