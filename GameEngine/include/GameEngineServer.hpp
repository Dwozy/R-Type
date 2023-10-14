/*
** EPITECH PROJECT, 2023
** GameEngineServer.hpp
** File description:
** GameEngineServer
*/

#ifndef GAMEENGINESERVER_HPP_
#define GAMEENGINESERVER_HPP_
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "utils/DeltaTime.hpp"
#include "utils/SfmlTypes.hpp"

namespace GameEngine
{
    class GameEngineServer
    {
      public:
        GameEngineServer(std::size_t maxEntities = 512) : registry(maxEntities) { deltaTime.update(); };
        ~GameEngineServer() = default;

        Registry registry;
        DeltaTime deltaTime;

      protected:
      private:
    };

}; // namespace GameEngine

#endif /* !GAMEENGINESERVER_HPP_ */
