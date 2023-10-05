/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Error
*/

#include "Error.hpp"

namespace Error
{
    ComponentNotRegisterError::ComponentNotRegisterError()
        : message("This component hasn't been registered")
    {
    }
    ComponentNotRegisterError::~ComponentNotRegisterError() {}
    char const *ComponentNotRegisterError::what() const noexcept
    {
        return message.c_str();
    }
} // namespace Error
