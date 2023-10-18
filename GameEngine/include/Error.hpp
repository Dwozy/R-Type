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
} // namespace Error

#endif /* !ERROR_HPP_ */
