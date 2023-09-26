/*
** EPITECH PROJECT, 2023
** ClientSession.hpp
** File description:
** ClientSession
*/

#ifndef CLIENTSESSION_HPP_
    #define CLIENTSESSION_HPP_

    #include <iostream>
    #include <boost/array.hpp>
    #include <boost/bind.hpp>
    #include <boost/enable_shared_from_this.hpp>
    #include <boost/shared_ptr.hpp>
    #include <boost/asio.hpp>

/// @brief Client Session that will handle every client's event
class ClientSession : public boost::enable_shared_from_this<ClientSession> {
    public:
        ClientSession(boost::asio::io_context &IOContext);
        ~ClientSession();

        /// @brief Get the socket of the client session
        /// @return the client boost::asio::ip::tcp::socket
        boost::asio::ip::tcp::socket &getSocket();

        /// @brief start that will waiting for a message from the client
        void start();

        /// @brief Get the pointer of 'this' object
        /// @return 'this'
        boost::shared_ptr<ClientSession> get();

        /// @brief handles the asynchronous wait on read for the client session
        /// @param error checked if error occures
        /// @param transferredBytes corresponding to the received bytes from client
        void handleRead(const boost::system::error_code &error, std::size_t transferredBytes);

        /// @brief handles the asynchronous wait on write to the client session
        /// @param error checked if error occures
        void handleWrite(const boost::system::error_code &error);

    protected:
    private:
        std::array<char, 1024> _readBuffer;
        boost::asio::ip::tcp::socket _socket;
};
#endif /* !CLIENTSESSION_HPP_ */
