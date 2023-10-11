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
    template<class T>
    class IFont
    {
        public:
            ~IFont() = default;
            virtual const T &getFont() const = 0;
            virtual void load(const std::string &filename)  = 0;
    };

    template <typename T, template <typename> class M>
    class IRect
    {
        public:
            ~IRect() = default;
            virtual const M<T> getBaseRect() const = 0;
    };

    template<class T, template <typename> class rectT>
    class ITexture
    {
        public:
            ~ITexture() = default;
            virtual const T &getTexture() const = 0;
            virtual void load(const std::string &filename, const IRect<int, rectT> &area) = 0;
    };

    template<class T, class TextuT, template <typename> class rectT>
    class ISprite
    {
        public:
            ~ISprite() = default;
            virtual const T &getSprite() const = 0;
            virtual void load(const ITexture<TextuT, rectT> &texture, bool resetRect = false) = 0;
            virtual void setPosition(const Vector2<float> position) = 0;
    };
    template<class T>
    class IEvent
    {
        public:
            virtual T &getEvent() = 0;
    };
    template<class T>
    class IView
    {
        public:
            ~IView() = default;
            virtual const T &getBaseView() const = 0;
    };
    template<class T, class Vt, class Et, class D>
    class IWindow
    {
        public:
        virtual ~IWindow() = default;
        virtual const T &getWindow() const = 0;
        virtual void draw(const D &drawable) = 0;
        virtual void setView(const IView<Vt> &view) = 0;
        virtual bool isOpen() const = 0;
        virtual bool pollEvent(IEvent<Et> &event) = 0;
        virtual void close() = 0;
        virtual void display() = 0;
        virtual void clear() = 0;
        virtual void create(int width, int height, const std::string &title) = 0;
    };
}

#endif /* !RENDERINTERFACES_HPP_ */
