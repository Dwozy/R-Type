/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** MainMenuScene
*/

#ifndef MAINMENUSCENE_HPP_
#define MAINMENUSCENE_HPP_
#include "utils/IScene.hpp"

class MainMenuScene : public GameEngine::IScene {
    public:
        MainMenuScene();
        ~MainMenuScene() = default;
        void load() override;
        void unload() override;

    protected:
    private:
};

#endif /* !MAINMENUSCENE_HPP_ */
