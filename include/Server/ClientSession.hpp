/*
** EPITECH PROJECT, 2023
** ClientSession.hpp
** File description:
** ClientSession
*/

#ifndef CLIENTSESSION_HPP_
#define CLIENTSESSION_HPP_

#include "SafeQueue.hpp"
#include <asio.hpp>
#include <iostream>

/// @brief Client Session that will handle every client's event
class ClientSession : public std::enable_shared_from_this<ClientSession>
{
  public:
    ClientSession(asio::io_context &IOContext,
                  SafeQueue<std::string> &clientsMessages);
    ~ClientSession();

    /// @brief Get the socket of the client session
    /// @return the client asio::ip::tcp::socket
    asio::ip::tcp::socket &getSocket();

    /// @brief start that will waiting for a message from the client
    void start();

    /// @brief Get the pointer of 'this' object
    /// @return 'this'
    std::shared_ptr<ClientSession> get();

    /// @brief handles the asynchronous wait on read for the client session
    /// @param error checked if error occures
    /// @param transferredBytes corresponding to the received bytes from client
    void handleRead(const asio::error_code &error,
                    std::size_t transferredBytes);

    /// @brief handles the asynchronous wait on write to the client session
    /// @param error checked if error occures
    void handleWrite(const asio::error_code &error);

  protected:
  private:
    asio::ip::tcp::socket _socket;
    SafeQueue<std::string> &_clientsMessages;
    std::array<char, 1024> _readBuffer;
};
#endif /* !CLIENTSESSION_HPP_ */
