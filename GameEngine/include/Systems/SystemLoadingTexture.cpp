/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemLoadingTexture
*/

namespace GameEngine
{
    class SystemLoadingTexture : public ISystem
    {
        public:
            SystemLoadingTexture(GameEngine &gameEngine): _gameEngine(gameEngine) {};
            virtual void update() override
            {
                for (const Entity &entity : entities)
                    _updateSingle(entity);
            };
            std::set<Entity> entities;
        protected:
            virtual void _updateSingle(const Entity &entity) override {};

            GameEngine &_gameEngine;
    };
}
