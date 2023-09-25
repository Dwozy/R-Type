/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ParserJson
*/

#ifndef PARSERJSON_HPP_
    #define PARSERJSON_HPP_
    #include <nlohmann/json.hpp>

using json = nlohmann::json;
class ParserJson {
    public:
        ParserJson();
        ~ParserJson();
    private:
};

#endif /* !PARSERJSON_HPP_ */
