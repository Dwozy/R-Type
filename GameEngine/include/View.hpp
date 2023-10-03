/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** View
*/

#ifndef VIEW_HPP_
#define VIEW_HPP_
#include "SFML/Graphics/Rect.hpp"
#include "utils/Rect.hpp"
#include <SFML/Graphics.hpp>

namespace GameEngine
{
    class View
    {
      public:
        View(const Rect<float> &rect)
            : _view{sf::Rect<float>{rect.left, rect.top, rect.width,
                                    rect.height}} {};
        ~View() = default;

        const sf::View &getBaseView() const { return _view; }

      private:
        sf::View _view;
    };
} // namespace GameEngine

#endif /* !VIEW_HPP_ */
