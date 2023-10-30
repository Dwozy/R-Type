/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
#define GAMESCENE_HPP_
#include "utils/IScene.hpp"

class GameScene : public GameEngine::IScene {
    public:
        GameScene();
        ~GameScene() = default;
        void load() override;
        void unload() override;

    protected:
    private:
};

#endif /* !GAMESCENE_HPP_ */
