/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ParserJson
*/


#ifndef PARSERJSON_HPP_
    #define PARSERJSON_HPP_
    #include <iostream>
    #include <fstream>
    #include <map>
    #include <string>
    #include <nolhmann/json.hpp>

    using json = nlohmann::json;

    class JsonParser
    {
        public:
            JsonParser(const std::string& filename);
            ~JsonParser() = default;

            std::string getData(const std::string& key);
        private:
            std::map<std::string, std::string> _dataMap;
    };

#endif /* !PARSERJSON_HPP_ */
