/*
** EPITECH PROJECT, 2023
** Error.hpp
** File description:
** Error
*/

#ifndef ERROR_HPP_
    #define ERROR_HPP_

    #include <exception>
    #include <string>

namespace Error {

    /**
     * @brief
     * NoEntityAvailable Class Error
     * Error thrown when trying to get entity that doesn't exist
     */
    class NoEntityAvailableError : public std::exception {
        public:
            NoEntityAvailableError();
            ~NoEntityAvailableError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * OutOfLimitEntitiesError Class Error
     * Error thrown when trying to get entity that doesn't exist
     */
    class OutOfEntitiesLimitError : public std::exception {
        public:
            OutOfEntitiesLimitError();
            ~OutOfEntitiesLimitError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * ComponentAlreadyAssignedError Class Error
     * Error thrown when trying to asign a component to an entity who already have this type of component asigned
     */
    class ComponentAlreadyAssignedError : public std::exception {
        public:
            ComponentAlreadyAssignedError();
            ~ComponentAlreadyAssignedError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * ComponentNotAsignedError Class Error
     * Error thrown when trying to remove a component from an entity who doesn't have this type of component
     */
    class ComponentNotAsignedError : public std::exception {
        public:
            ComponentNotAsignedError();
            ~ComponentNotAsignedError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * ComponentAlreadyRegisterError Class Error
     * Error thrown when trying to register a component who is already registered
     */
    class ComponentAlreadyRegisterError : public std::exception {
        public:
            ComponentAlreadyRegisterError();
            ~ComponentAlreadyRegisterError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * ComponentNotRegisterError Class Error
     * Error thrown when trying to access a component that is not registered
     */
    class ComponentNotRegisterError : public std::exception {
        public:
            ComponentNotRegisterError();
            ~ComponentNotRegisterError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * ComponentNotRegisterError Class Error
     * Error thrown when trying to register a system who is already registered
     */
    class SystemAlreadyRegisterError : public std::exception {
        public:
            SystemAlreadyRegisterError();
            ~SystemAlreadyRegisterError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };

    /**
     * @brief
     * ComponentNotRegisterError Class Error
     * Error thrown when trying to access a system that is not registered
     */
    class SystemNotRegisterError : public std::exception {
        public:
            SystemNotRegisterError();
            ~SystemNotRegisterError();
            const char *what() const noexcept override;
        private:
            std::string message;
    };
};

#endif /* !ERROR_HPP_ */
