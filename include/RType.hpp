/*
** EPITECH PROJECT, 2023
** RType.hpp
** File description:
** RType
*/

#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

    #include <utility>
    #include <string>
    #include <map>

namespace rtype {

    struct Entity {
        std::pair<float, float> position;
        std::pair<float, float> direction;
        std::size_t lifePoint;
        struct Player playerInfo;
    };

    struct Player {
        std::string name;
    };

    struct Room {
        std::size_t id; // unique
        std::size_t slots;
        std::size_t slotsLeft;
        std::string name;
        std::size_t stageLevel;
        std::map<std::size_t, struct Player> listPlayers;
    };


}

#endif /* !RTYPE_HPP_ */
