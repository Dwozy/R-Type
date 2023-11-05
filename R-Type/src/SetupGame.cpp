/*
** EPITECH PROJECT, 2023
** SetupGame.cpp
** File description:
** SetupGame
*/

#include "RTypeClient.hpp"
#include "components/TextComponent.hpp"
#include "GameEngine.hpp"

namespace RType::Client
{
    void RTypeClient::setupScoreText()
    {
        GameEngine::Entity scoreTitle = _gameEngine.registry.spawnEntity();
        GameEngine::TextComponent textTitle{"SCORE : ", "R-Type/fonts/Valoon.ttf", 10, GameEngine::Text(), true, 10};
        textTitle.text.load(textTitle.str, _gameEngine.assetManager.getFont("R-Type/fonts/Valoon.ttf").getFont(), textTitle.size);
        textTitle.text.setPosition(GameEngine::Vector2<float>{5, 5});
        _gameEngine.registry.addComponent<GameEngine::TextComponent>(scoreTitle, textTitle);

        GameEngine::Entity score = _gameEngine.registry.spawnEntity();
        GameEngine::TextComponent text{std::to_string(_points), "R-Type/fonts/Valoon.ttf", 10, GameEngine::Text(), true, 10};
        text.text.load(text.str, _gameEngine.assetManager.getFont("R-Type/fonts/Valoon.ttf").getFont(), text.size);
        text.text.setPosition(GameEngine::Vector2<float>{50, 5});
        _gameEngine.registry.addComponent<GameEngine::TextComponent>(score, text);
        _scoreTextEntity = score;
    }

    void RTypeClient::setupTextureEntity()
    {
        _listPathTextureId.insert(
            {static_cast<uint8_t>(RType::Protocol::TextureType::PLAYER), "R-Type/assets/image.png"});
        _listPathTextureId.insert(
            {static_cast<uint8_t>(RType::Protocol::TextureType::SIMPLE_MOB), "R-Type/assets/pata_pata.gif"});
        _listPathTextureId.insert(
            {static_cast<uint8_t>(RType::Protocol::TextureType::MEDIUM_MOB), "R-Type/assets/big_enemy.png"});
        _listPathTextureId.insert(
            {static_cast<uint8_t>(RType::Protocol::TextureType::SIMPLE_SHOOT), "R-Type/assets/player_projectile.png"});
        _listPathTextureId.insert({static_cast<uint8_t>(RType::Protocol::TextureType::CHARGED_SHOOT),
            "R-Type/assets/player_projectile_charged.png"});
    }

    void RTypeClient::setupGame()
    {
        setupTextureEntity();
        auto parallaxCallback = std::bind(&RType::Client::RTypeClient::parallaxCollision, this,
        std::placeholders::_1,
            std::placeholders::_2, std::placeholders::_3);
        GameEngine::Entity camera = _gameEngine.registry.spawnEntity();
        GameEngine::CameraComponent cam = {GameEngine::View{GameEngine::Rect<float>(0.0f, 0.0f, 200.0f, 200.0f)}};
        auto &refCamera = _gameEngine.registry.addComponent<GameEngine::CameraComponent>(camera, cam);

        if (refCamera)
            _gameEngine.eventManager.publish<GameEngine::View &>(
                static_cast<GameEngine::EventType>(GameEngine::Event::WindowSetView), refCamera.value().view);

        auto parallax1 = _gameEngine.prefabManager.createEntityFromPrefab("parallax", _gameEngine.registry);
        auto &textureParallax = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[parallax1];
        textureParallax->sprite.setScale(0.1851, 0.1851);

        auto parallax2 = _gameEngine.prefabManager.createEntityFromPrefab("parallax", _gameEngine.registry);
        auto &posParallax2 = _gameEngine.registry.getComponent<GameEngine::TransformComponent>()[parallax2];
        posParallax2.value().position = GameEngine::Vector2<float>(199.0, 0.0);
        auto &textureParallax2 = _gameEngine.registry.getComponent<GameEngine::TextureComponent>()[parallax2];
        textureParallax2->sprite.setScale(0.1851, 0.1851);

        auto parallaxRange =
            _gameEngine.prefabManager.createEntityFromPrefab("parallaxCollision", _gameEngine.registry);
        auto &parallaxBox = _gameEngine.registry.getComponent<GameEngine::CollisionComponent>()[parallaxRange];
        parallaxBox.value()
            .addAction<std::function<void(const std::size_t &, SparseArray<GameEngine::CollisionComponent> &,
                           SparseArray<GameEngine::TransformComponent> &)>,
                GameEngine::CollisionComponent, GameEngine::TransformComponent>(_gameEngine.registry,
                parallaxCallback);
    }
} // namespace RType::Client
