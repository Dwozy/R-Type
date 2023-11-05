/*
 ** EPITECH PROJECT, 2023
 ** R-type
 ** File description:
 ** JsonConversion
 */

#ifndef JSONCONVERSION_HPP_
#define JSONCONVERSION_HPP_
#include <nlohmann/json.hpp>
#include <iostream>
#include "components/CameraComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ControllableComponent.hpp"
#include "components/MusicComponent.hpp"
#include "components/PressableComponent.hpp"
#include "components/TextComponent.hpp"
#include "components/TextureComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/HealthComponent.hpp"
#include "components/DamageComponent.hpp"
#include "components/GravityComponent.hpp"

using json = nlohmann::json;

namespace GameEngine::Input::Keyboard
{
    const std::unordered_map<std::string, Key> strKeyMap = {{"A", A}, {"B", B}, {"C", C}, {"D", D}, {"E", E}, {"F", F},
        {"G", G}, {"H", H}, {"I", I}, {"J", J}, {"K", K}, {"L", L}, {"M", M}, {"N", N}, {"O", O}, {"P", P}, {"Q", Q},
        {"R", R}, {"S", S}, {"T", T}, {"U", U}, {"V", V}, {"W", W}, {"X", X}, {"Y", Y}, {"Z", Z}, {"Num0", Num0},
        {"Num1", Num1}, {"Num2", Num2}, {"Num3", Num3}, {"Num4", Num4}, {"Num5", Num5}, {"Num6", Num6}, {"Num7", Num7},
        {"Num8", Num8}, {"Num9", Num9}, {"Escape", Escape}, {"LControl", LControl}, {"LShift", LShift}, {"LAlt", LAlt},
        {"LSystem", LSystem}, {"RControl", RControl}, {"RShift", RShift}, {"RAlt", RAlt}, {"RSystem", RSystem},
        {"Menu", Menu}, {"LBracket", LBracket}, {"RBracket", RBracket}, {"Semicolon", Semicolon}, {"Comma", Comma},
        {"Period", Period}, {"Quote", Quote}, {"Slash", Slash}, {"Backslash", Backslash}, {"Tilde", Tilde},
        {"Equal", Equal}, {"Dash", Dash}, {"Space", Space}, {"Enter", Enter}, {"Backspace", Backspace}, {"Tab", Tab},
        {"Add", Add}, {"Subtract", Subtract}, {"Multiply", Multiply}, {"Divide", Divide}, {"Left", Left},
        {"Right", Right}, {"Up", Up}, {"Down", Down}, {"Numpad0", Numpad0}, {"Numpad1", Numpad1}, {"Numpad2", Numpad2},
        {"Numpad3", Numpad3}, {"Numpad4", Numpad4}, {"Numpad5", Numpad5}, {"Numpad6", Numpad6}, {"Numpad7", Numpad7},
        {"Numpad8", Numpad8}, {"Numpad9", Numpad9}, {"F1", F1}, {"F2", F2}, {"F3", F3}, {"F4", F4}, {"F5", F5},
        {"F6", F6}, {"F7", F7}, {"F8", F8}, {"F9", F9}, {"F10", F10}, {"F11", F11}, {"F12", F12}, {"F13", F13},
        {"F14", F14}, {"F15", F15}, {"Pause", Pause}, {"No_Key", NO_KEY}};
};

namespace GameEngine
{
    /// @brief Function to convert a json object to a key
    /// @param j reference to the json object
    /// @param key reference to the key
    void from_json(const json &j, Input::Keyboard::Key &key)
    {
        auto str = j.get<std::string>();
        key = Input::Keyboard::strKeyMap.at(str);
    }

    /// @brief Function to convert a json object to a rect
    /// @tparam T type of the rect
    /// @param j reference to the json object
    /// @param rect reference to the rect
    template <typename T>
    void from_json(const json &j, Rect<T> &rect)
    {
        j.at("left").get_to(rect.left);
        j.at("top").get_to(rect.top);
        j.at("width").get_to(rect.width);
        j.at("height").get_to(rect.height);
    }

    template <typename T>
    void from_json(const json &j, Vector2<T> &vec)
    {
        j.at("x").get_to(vec.x);
        j.at("y").get_to(vec.y);
    }
    /// @brief Function to convert a json object to a Texture
    /// @param j reference to the json object
    /// @param texture reference to the texture
    void from_json(const json &j, Texture &texture)
    {
        std::string path(j.at("path").get<std::string>());
        Rect<int> area;
        j.at("area").get_to(area);
        texture.load(path, area);
    }

    /// @brief Function to convert a json object to a TransfromComponent
    /// @param j reference to the json object
    /// @param tc reference to the transform component
    void from_json(const json &j, TransformComponent &tc)
    {
        j.at("position").get_to(tc.position);
        j.at("velocity").get_to(tc.velocity);
    }

    /// @brief Function to convert a json object to a HealthComponent
    /// @param j reference to the json object
    /// @param tc reference to the health component
    void from_json(const json &j, HealthComponent &hc)
    {
        hc.health = j.contains("health") ? j.at("health").get<int>() : 5;
    }

    /// @brief Function to convert a json object to a DamageComponent
    /// @param j reference to the json object
    /// @param tc reference to the damage component
    void from_json(const json &j, DamageComponent &dc) { j.at("damage").get_to(dc.damage); }

    /// @brief Function to convert a json object to a ControllableComponent
    /// @param j reference to the json object
    /// @param cc reference to the controllable component
    void from_json(const json &j, ControllableComponent &cc)
    {
        cc.key_up = Input::Keyboard::strKeyMap.at(j.at("key_up").get<std::string>());
        cc.key_down = Input::Keyboard::strKeyMap.at(j.at("key_down").get<std::string>());
        cc.key_left = Input::Keyboard::strKeyMap.at(j.at("key_left").get<std::string>());
        cc.key_right = Input::Keyboard::strKeyMap.at(j.at("key_right").get<std::string>());
        j.at("speed").get_to(cc.speed);
    }

    /// @brief Function to convert a json object to a TextureComponent
    /// @param j reference to the json object
    /// @param tc reference to the texture component
    void from_json(const json &j, TextureComponent &tc)
    {
        j.at("texturePath").get_to(tc.path);
        j.at("textureSize").get_to(tc.textureSize);
        tc.animated = j.contains("animated") ? j.at("animated").get<bool>() : false;
        for (auto &trect : j.at("textureRects"))
            tc.textureRects.push_back(trect);
        tc.animationSpeed = j.contains("animationSpeed") ? j.at("animationSpeed").get<float>() : 0.0f;
        tc.isRendered = j.contains("isRendered") ? j.at("isRendered").get<bool>() : true;
        tc.lastUpdate = j.contains("lastUpdate") ? j.at("lastUpdate").get<float>() : 0.0f;
        tc.animeid = 0;
        j.at("renderLayer").get_to(tc.renderLayer);
    }

    /// @brief Function to convert a json object to a CollisionComponent
    /// @param j reference to the json object
    /// @param cc reference to the collision component
    void from_json(const json &j, CollisionComponent &cc)
    {
        j.at("collider").get_to(cc.collider);
        j.at("layer").get_to(cc.layer);
        cc.isActive = j.contains("isActive") ? j.at("isActive").get<bool>() : true;
    }

    /// @brief Function to convert a json object to a GravityComponent
    /// @param j reference to the json object
    /// @param gc reference to the gravity component
    void from_json(const json &j, GravityComponent &gc)
    {
        j.at("gravityForce").get_to(gc.gravityForce);
        j.at("isActive").get_to(gc.isActive);
    }

    /// @brief Function to convert a json object to a CameraComponent
    /// @param j reference to the json object
    /// @param cc reference to the camera component
    void from_json(const json &j, CameraComponent &cc)
    {
        auto rect = j.at("cameraView").get<Rect<float>>();
        cc.view = GameEngine::View(rect);
        if (j.contains("cameraViewport")) {
            rect = j.at("cameraViewport").get<Rect<float>>();
            cc.view.setViewPort({rect.left, rect.top}, rect.width, rect.height);
        }
        if (j.contains("follow_x"))
            j.at("follow_x").get_to(cc.follow_x);
        if (j.contains("follow_y"))
            j.at("follow_y").get_to(cc.follow_y);
        if (j.contains("isActive"))
            j.at("isActive").get_to(cc.isActive);
    }

    void from_json(const json &j, TextComponent &tx)
    {
        tx.text = GameEngine::Text();
        j.at("str").get_to(tx.str);
        j.at("size").get_to(tx.size);
        j.at("fontPath").get_to(tx.fontPath);
        tx.isRendered = j.contains("isRendered") ? j.at("isRendered").get<bool>() : true;
        j.at("renderLayer").get_to(tx.renderLayer);
    }
} // namespace GameEngine

#endif /* !JSONCONVERSION_HPP_ */
