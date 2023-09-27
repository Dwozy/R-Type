/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ParserJson
*/

// #include "ParserJson.hpp"

// JsonParser::JsonParser(const std::string& filename)
// {
//     std::ifstream file(filename);
//     if (file.is_open()) {
//         json jsonData;
//         file >> jsonData;
//         file.close();
//         for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
//             if (it->is_string()) {
//                 _dataMap[it.key()] = it->get<std::string>();
//             }
//         }
//     } else {
//         std::cerr << "Failed to open JSON file: " << filename << std::endl;
//     }
// }

// std::string JsonParser::getData(const std::string& key)
// {
//     if (_dataMap.count(key)) {
//         return _dataMap[key];
//     } else {
//         return std::string();
//     }
// }
