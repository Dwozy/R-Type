/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RenderInterfaces
*/

#ifndef RENDERINTERFACES_HPP_
    #define RENDERINTERFACES_HPP_
    #include <string>
    #include "utils/Vector.hpp"

namespace GameEngine
{
    /// @brief Interfaces for the text font
    /// @tparam T type of the font
    template<class T>
    class IFont
    {
        public:
            /// @brief Destructor
            ~IFont() = default;
            /// @brief Get the font that will be stored
            /// @return Reference to the font
            virtual const T &getFont() const = 0;
            /// @brief Load the font
            /// @param filename File from which to load the font
            virtual void load(const std::string &filename)  = 0;
    };

    /// @brief Interface for rectangle
    /// @tparam T type of the rectangle
    template <typename T, template <typename> class M>
    class IRect
    {
        public:
            /// @brief Destructor
            ~IRect() = default;
            /// @brief Get the rectangle stored
            /// @return rectangle stored
            virtual const M<T> getBaseRect() const = 0;
    };

    /// @brief Interface for texture
    /// @tparam T type of the texture
    /// @tparam rectT type of rect that will be used
    template<class T, template <typename> class rectT>
    class ITexture
    {
        public:
            /// @brief Destructor
            ~ITexture() = default;
            /// @brief Get the texture stored
            /// @return reference to the texture
            virtual const T &getTexture() const = 0;
            /// @brief  load the texture
            /// @param filename file from which to load the texture
            /// @param area the area of the texture
            virtual void load(const std::string &filename, const IRect<int, rectT> &area) = 0;
    };

    /// @brief interface for music handling
    /// @tparam MusicType type of the music
    template <typename MusicType>
    class IMusic
    {
    public:
        /// @brief destructor
       ~IMusic() = default;
        /// @brief Get the wrapped music instance
        /// @return Reference to the music instance
        virtual const MusicType &getMusic() const = 0;
        /// @brief Load music from a file
        /// @param filename The path to the music file
        virtual void load(const std::string &filename) = 0;
    };

    /// @brief Interface for sprite
    /// @tparam T template type of sprite
    /// @tparam TextuT type of texture
    /// @tparam rectT type of rect
    template<class T, class TextuT, template <typename> class rectT>
    class ISprite
    {
        public:
            /// @brief Destructor
            ~ISprite() = default;
            /// @brief Get the sprite stored
            /// @return return the sprite
            virtual const T &getSprite() const = 0;
            /// @brief load the sprite
            /// @param texture texture from which to load the sprite
            /// @param resetRect boolean to reset the sprite rectangle
            virtual void load(const ITexture<TextuT, rectT> &texture, bool resetRect = false) = 0;
            /// @brief set the position of the sprite
            /// @param position new position of the sprite
            virtual void setPosition(const Vector2<float> position) = 0;
            /// @brief set a new rect forof the sprite
            /// @param newRect new rect of the sprite
            virtual void setTextureRect(const IRect<int, rectT> &newRect) = 0;
    };

    /// @brief Interface for event
    /// @tparam T type on event
    template<class T>
    class IEvent
    {
        public:
            /// @brief Get the event stored
            /// @return event stored
            virtual T &getEvent() = 0;
    };

    /// @brief Interface for view
    /// @tparam T type of view
    template<class T>
    class IView
    {
        public:
            /// @brief Destructor
            ~IView() = default;
            /// @brief Get the view stored
            /// @return the view
            virtual const T &getBaseView() const = 0;
    };

    /// @brief Interface for the window
    /// @tparam T type of the window
    /// @tparam Vt type of view
    /// @tparam Et type of event
    /// @tparam D type of drawable
    template<class T, class Vt, class Et, class D>
    class IWindow
    {
        public:
        /// @brief Destructor
        virtual ~IWindow() = default;
        /// @brief Get the window
        /// @return the window
        virtual const T &getWindow() const = 0;
        /// @brief draw a drawable on the window
        /// @param drawable object that can be draw
        virtual void draw(const D &drawable) = 0;
        /// @brief set a new view in the window
        /// @param view the window will take
        virtual void setView(const IView<Vt> &view) = 0;
        /// @brief  check if the window is open
        /// @return boolean indicating that the window is open
        virtual bool isOpen() const = 0;
        /// @brief pop the event on top of the event queue, if any, and return it.
        /// @param event class that take the event
        /// @return boolean
        virtual bool pollEvent(IEvent<Et> &event) = 0;
        /// @brief close the window
        virtual void close() = 0;
        /// @brief display everything that has been drawn
        virtual void display() = 0;
        /// @brief clear the window
        virtual void clear() = 0;
        /// @brief create a new window
        /// @param width width of the window
        /// @param height height of the window
        /// @param title title of the window
        virtual void create(int width, int height, const std::string &title) = 0;
    };
}

#endif /* !RENDERINTERFACES_HPP_ */
