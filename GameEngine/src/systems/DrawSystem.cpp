/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemDraw
*/
#include "systems/DrawSystem.hpp"
#include "components/TextComponent.hpp"
#include "components/TextureComponent.hpp"
#include "systems/DrawSystem.hpp"
#include "components/TextComponent.hpp"
#include "components/TextureComponent.hpp"
#include "utils/SfmlTypes.hpp"
#include "Mouse.hpp"
#include <algorithm>
#include <utility>
#include <algorithm>
#include <utility>
#include <variant>
#include <vector>

namespace GameEngine
{
    DrawSystem::DrawSystem(EventManager &eventManager, int width, int height, std::string title)
        : _eventManager(eventManager)
    {
        _window = std::make_shared<Window>(width, height, title);
        auto &isOpenHandler = _eventManager.addHandler<bool &>(static_cast<EventType> (Event::WindowIsOpen));
        auto &pollEventHandler = _eventManager.addHandler<PollEventStruct &>(static_cast<EventType>  (Event::PollEvent));
        auto &windowCloseHandler = _eventManager.addHandler<SEvent &>(static_cast<EventType>  (Event::WindowCloseEvent));
        auto &getWorldMousePosHandler = _eventManager.addHandler<Vector2<float> &>(static_cast<EventType> (Event::GetWorldMousePos));
        auto &WindowSetViewHandler = _eventManager.addHandler<View &>(static_cast<EventType> (Event::WindowSetView));

        _window->setFramerateLimit(60);
        isOpenHandler.subscribe([this](bool &isOpen) { isOpen = this->_window->isOpen(); });
        pollEventHandler.subscribe(
            [this](PollEventStruct &pollEvent) { pollEvent.isEvent = _window->pollEvent(pollEvent.event); });
        windowCloseHandler.subscribe([this](SEvent &event) {
            if (event.type == sf::Event::Closed)
                _window->close();
        });
        getWorldMousePosHandler.subscribe([this](Vector2<float> &pos) {
            pos = this->_window->mapPixelToCoords(Input::Mouse::getPosition(*this->_window));
        });
        WindowSetViewHandler.subscribe([this](View &view) { this->_window->setView(view); });
    }

    void DrawSystem::operator()(SparseArray<TextComponent> &texts, SparseArray<TextureComponent> &textures)
    {
        std::vector<std::variant<TextureComponent, TextComponent>> rend;
        _window->clear();

        for (size_t i = 0; i < texts.size(); i++) {
            auto &tex = texts[i];
            if (tex)
                rend.push_back(tex.value());
        }

        for (size_t i = 0; i < textures.size(); i++) {
            auto &tex = textures[i];
            if (tex)
                rend.push_back(tex.value());
        }

        std::sort(rend.begin(), rend.end(),
            [](const std::variant<TextureComponent, TextComponent> &a,
                const std::variant<TextureComponent, TextComponent> &b) {
                if (std::holds_alternative<TextureComponent>(a) && std::holds_alternative<TextureComponent>(b))
                    return std::get<TextureComponent>(a).renderLayer < std::get<TextureComponent>(b).renderLayer;
                if (std::holds_alternative<TextureComponent>(a) && std::holds_alternative<TextComponent>(b))
                    return std::get<TextureComponent>(a).renderLayer < std::get<TextComponent>(b).renderLayer;
                if (std::holds_alternative<TextComponent>(a) && std::holds_alternative<TextureComponent>(b))
                    return std::get<TextComponent>(a).renderLayer < std::get<TextureComponent>(b).renderLayer;
                if (std::holds_alternative<TextComponent>(a) && std::holds_alternative<TextComponent>(b))
                    return std::get<TextComponent>(a).renderLayer < std::get<TextComponent>(b).renderLayer;
                return false;
            });

        for (const auto &item : rend) {
            if (std::holds_alternative<TextureComponent>(item)) {
                const auto &tex = std::get<TextureComponent>(item);
                _window->draw(tex.sprite.getSprite());
            } else if (std::holds_alternative<TextComponent>(item)) {
                const auto &tex = std::get<TextComponent>(item);
                _window->draw(tex.text.getText());
            }
        }
        _window->display();
    }
} // namespace GameEngine
