/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** inputs
*/

#include "utils/SfmlTypes.hpp"
#include <unordered_map>
#include "Keyboard.hpp"

// Define and initialize the static member variable
const std::unordered_map<GameEngine::Input::Keyboard::Key, sf::Keyboard::Key> GameEngine::InputManager::sfKeys = {
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


std::unordered_map<GameEngine::Input::Keyboard::Key, bool> GameEngine::InputManager::prevKeyStates;
