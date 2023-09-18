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
     * OutOfLimitEntities Class Error
     * Error thrown when trying to get entity that doesn't exist
     */
    class OutOfEntitiesLimit : public std::exception {
        public:
            OutOfEntitiesLimit();
            ~OutOfEntitiesLimit();
            const char *what() const noexcept override;
        private:
            std::string message;
    };
};

#endif /* !ERROR_HPP_ */
