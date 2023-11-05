/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Error
*/

#include "Error.hpp"

namespace Error
{
    ComponentNotRegisterError::ComponentNotRegisterError() : message("This component hasn't been registered") {}
    ComponentNotRegisterError::~ComponentNotRegisterError() {}
    char const *ComponentNotRegisterError::what() const noexcept { return message.c_str(); }

    ComponentNotInsertedError::ComponentNotInsertedError() : message("This component hasn't been inserted") {}
    ComponentNotInsertedError::~ComponentNotInsertedError() {}
    char const *ComponentNotInsertedError::what() const noexcept { return message.c_str(); }

    TooMuchEntitiesError::TooMuchEntitiesError() : message("Too much entities have been created") {}
    TooMuchEntitiesError::~TooMuchEntitiesError() {}
    char const *TooMuchEntitiesError::what() const noexcept { return message.c_str(); }

    InvalidEntityIdError::InvalidEntityIdError() : message("Invalid id entity") {}
    InvalidEntityIdError::~InvalidEntityIdError() {}
    char const *InvalidEntityIdError::what() const noexcept { return message.c_str(); }

    InvalidSceneNameError::InvalidSceneNameError() : message("The scene name is invalid or already used") {}
    InvalidSceneNameError::~InvalidSceneNameError() {}
    char const *InvalidSceneNameError::what() const noexcept { return message.c_str(); }

    SceneNotRegisterError::SceneNotRegisterError() : message("The scene hasn't been registered") {}
    SceneNotRegisterError::~SceneNotRegisterError() {}
    char const *SceneNotRegisterError::what() const noexcept { return message.c_str(); }

    InvalidPrefabFileError::InvalidPrefabFileError() : message("Invalid prefab config file") {}
    InvalidPrefabFileError::~InvalidPrefabFileError() {}
    char const *InvalidPrefabFileError::what() const noexcept { return message.c_str(); }

    PrefabNameAlreadyUsedError::PrefabNameAlreadyUsedError() : message("Prefab name already used") {}
    PrefabNameAlreadyUsedError::~PrefabNameAlreadyUsedError() {}
    char const *PrefabNameAlreadyUsedError::what() const noexcept { return message.c_str(); }

#ifdef DEBUG
    ImGuiSFMLInitError::ImGuiSFMLInitError() : message("Failed to init ImGui-SFML context") {}
    ImGuiSFMLInitError::~ImGuiSFMLInitError() {}
    char const *ImGuiSFMLInitError::what() const noexcept { return message.c_str(); }
#endif

} // namespace Error
