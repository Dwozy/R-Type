/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Ennemies
*/

#ifndef ENNEMIES_HPP_
    #define ENNEMIES_HPP_
    #include <unordered_map>
    #include <string>
    #include <iostream>
    #include <functional>
    #include "GameEngine.hpp"

class Ennemie {
    public:
        Ennemie(GameEngine::GameEngine &gameEngine, GameEngine::PositionComponent pos,
        GameEngine::VelocityComponent vel,
        GameEngine::TextureAnimatedComponent tex, GameEngine::Texture &texture, GameEngine::Sprite &sprite) : _ennemies(gameEngine.registry.spawnEntity()), _pos(pos), _vel(vel), _tex(tex), _texture(texture), _sprite(sprite)
        {
            std::cout << "Ennemie created" << std::endl;
            gameEngine.registry.addComponent<GameEngine::PositionComponent>(_ennemies, _pos);
            gameEngine.registry.addComponent<GameEngine::VelocityComponent>(_ennemies, _vel);
            gameEngine.registry.addComponent<GameEngine::TextureAnimatedComponent>(_ennemies, _tex);
        };
        ~Ennemie() {
            std::cout << "destroyed" << std::endl;
        };
        void death() {};
        void updatePose() {};
        void updateVelocity() {};
        void updateTexture() {};
    private:
        GameEngine::Entity _ennemies;
        GameEngine::PositionComponent _pos;
        GameEngine::VelocityComponent _vel;
        GameEngine::TextureAnimatedComponent _tex;
        GameEngine::Texture &_texture;
        GameEngine::Sprite &_sprite;
};

Ennemie create_Pata_Pata(GameEngine::GameEngine &gameEngine);

class Ennemies
{
    public:
        Ennemies(GameEngine::GameEngine &GameEngine) : _gameEngine(GameEngine) {
            _all_ennemies.insert({Pata_Pata, create_Pata_Pata});
        };
        ~Ennemies() = default;
        enum Name_Ennemie
        {
            POW_Armor,
            Pata_Pata,
            Bink,
            Scant,
            Bug,
            Cancer,
            P_Staff,
            Blaster,
            Shell,
            Tabrok,
            Gouger,
            Brood,
            Zoid,
            Wick,
            Worm,
            Cytron,
            Geld,
            Slither,
            Pursuer,
            Cheetah,
            Mid,
            Dop,
            Newt,
            Bold,
            Fast,
            Sonar,
            Mikun,
            Win,
        };
        void create_ennemie(size_t id, Name_Ennemie name);
        Ennemie &get_ennemie(size_t id);
        void destroy_ennemie(size_t id);
    private:
        GameEngine::GameEngine &_gameEngine;
        std::unordered_map<size_t, Ennemie> _ennemies;
        std::unordered_map<Name_Ennemie, std::function<Ennemie(GameEngine::GameEngine &)>> _all_ennemies;
};
#endif /* !ENNEMIES_HPP_ */
