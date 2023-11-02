/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <exception>
#include <string>

namespace Error
{
    /**
     * @brief
     * ComponentNotRegisterError Class Error
     * Error thrown when trying to access a component that is not register
     */
    class ComponentNotRegisterError : public std::exception
    {
      public:
        ComponentNotRegisterError();
        ~ComponentNotRegisterError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };

    /**
     * @brief
     * ComponentNotInsertedError Class Error
     * Error thrown when trying to access a component that is not register
     */
    class ComponentNotInsertedError : public std::exception
    {
      public:
        ComponentNotInsertedError();
        ~ComponentNotInsertedError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };

    /**
     * @brief
     * TooMuchEntitiesError Class Error
     * Error thrown when exceeding the maximum number of entities
     */
    class TooMuchEntitiesError : public std::exception
    {
      public:
        TooMuchEntitiesError();
        ~TooMuchEntitiesError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };

    /**
     * @brief
     * TooMuchEntitiesError Class Error
     * Error thrown when exceeding the maximum number of entities
     */
    class InvalidEntityIdError : public std::exception
    {
      public:
        InvalidEntityIdError();
        ~InvalidEntityIdError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };

    /**
     * @brief
     * InvalidSceneNameError Class Error
     * Error thrown when registering a scene with an invalid name or already used name.
     */
    class InvalidSceneNameError : public std::exception
    {
      public:
        InvalidSceneNameError();
        ~InvalidSceneNameError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };

    /**
     * @brief
     * SceneNotRegisterError Class Error
     * Error thrown when trying to access a scene that is not registered.
     */
    class SceneNotRegisterError : public std::exception
    {
      public:
        SceneNotRegisterError();
        ~SceneNotRegisterError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };
    /**
     * @brief
     * InvalidPrefabFileError Class Error
     * Error thrown when trying to parse a prefab config file that does not exist or is invalid.
     */
    class InvalidPrefabFileError : public std::exception
    {
      public:
        InvalidPrefabFileError();
        ~InvalidPrefabFileError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };
    /**
     * @brief
     * PrefabNameAlreadyUsedError Class Error
     * Error thrown when trying to add a prefab with a name that is already used
     */
    class PrefabNameAlreadyUsedError : public std::exception
    {
      public:
        PrefabNameAlreadyUsedError();
        ~PrefabNameAlreadyUsedError();
        const char *what() const noexcept override;

      private:
        std::string message;
    };
} // namespace Error

#endif /* !ERROR_HPP_ */
