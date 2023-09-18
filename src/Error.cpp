/*
** EPITECH PROJECT, 2023
** Error.cpp
** File description:
** Error
*/

#include "Error.hpp"

namespace Error {

    NoEntityAvailableError::NoEntityAvailableError(): message("Not entity available") {}
    NoEntityAvailableError::~NoEntityAvailableError() {}
    char const *NoEntityAvailableError::what() const noexcept { return message.c_str(); }

    OutOfEntitiesLimit::OutOfEntitiesLimit(): message("Too many entities available") {}
    OutOfEntitiesLimit::~OutOfEntitiesLimit() {}
    char const *OutOfEntitiesLimit::what() const noexcept { return message.c_str(); }

}
