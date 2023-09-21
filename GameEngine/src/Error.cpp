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

    OutOfEntitiesLimitError::OutOfEntitiesLimitError(): message("Too many entities available") {}
    OutOfEntitiesLimitError::~OutOfEntitiesLimitError() {}
    char const *OutOfEntitiesLimitError::what() const noexcept { return message.c_str(); }

    ComponentAlreadyAssignedError::ComponentAlreadyAssignedError(): message("This entity has already a component asign for this component type") {}
    ComponentAlreadyAssignedError::~ComponentAlreadyAssignedError() {}
    char const *ComponentAlreadyAssignedError::what() const noexcept { return message.c_str(); }

    ComponentNotAsignedError::ComponentNotAsignedError(): message("This entity doesn't have a component asign for this component type") {}
    ComponentNotAsignedError::~ComponentNotAsignedError() {}
    char const *ComponentNotAsignedError::what() const noexcept { return message.c_str(); }

    ComponentAlreadyRegisterError::ComponentAlreadyRegisterError(): message("This component has already been registered") {}
    ComponentAlreadyRegisterError::~ComponentAlreadyRegisterError() {}
    char const *ComponentAlreadyRegisterError::what() const noexcept { return message.c_str(); }

    ComponentNotRegisterError::ComponentNotRegisterError(): message("This component hasn't been registered") {}
    ComponentNotRegisterError::~ComponentNotRegisterError() {}
    char const *ComponentNotRegisterError::what() const noexcept { return message.c_str(); }

}
