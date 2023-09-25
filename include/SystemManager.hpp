/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
    #define SYSTEMMANAGER_HPP_
    #include <unordered_map>
    #include <string>
    #include <memory>
    #include "System.hpp"

namespace GameEngine
{
    class SystemManager
    {
        public:
            ~SystemManager() = default;

            template<typename SysType>
            std::shared_ptr<SysType> registerSystem(GameEngine &gameEngine)
            {
                std::string typeId(typeid(SysType).name());
                std::shared_ptr<SysType> system;

                if (_systems.find(typeId) != _systems.end())
                    throw Error::SystemAlreadyRegisterError();
                system = std::make_shared<SysType>(gameEngine);
                _systems.insert({ typeId, system });
                return system;
            };

            template<typename SysType>
            std::shared_ptr<SysType> getSystem()
            {
                std::string typeId(typeid(SysType).name());
                std::shared_ptr<SysType> system;

                if (_systems.find(typeId) == _systems.end())
                    throw Error::SystemNotRegisterError();
                system = std::static_pointer_cast<SysType>(_systems[typeId]);
                return system;
            };

            template<typename SysType>
            void assignSystem(Entity entity)
            {
                getSystem<SysType>()->entities.insert(entity);
            }

            void entityDestroyed(Entity entity)
            {
                for (auto &sys : _systems)
                {
                    if (sys.second->entities.find(entity) != sys.second->entities.end())
                        sys.second->entities.erase(entity);
                }
            }
        private:
            std::unordered_map<std::string, std::shared_ptr<SystemBase>> _systems;
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */
