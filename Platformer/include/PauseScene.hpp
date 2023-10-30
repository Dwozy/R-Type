/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-timothe.zheng
** File description:
** PauseScene
*/

#ifndef PAUSESCENE_HPP_
#define PAUSESCENE_HPP_
#include "utils/IScene.hpp"

class PauseScene : public GameEngine::IScene {
    public:
        PauseScene();
        ~PauseScene() = default;
        void load() override;
        void unload() override;

    protected:
    private:
};

#endif /* !PAUSESCENE_HPP_ */
