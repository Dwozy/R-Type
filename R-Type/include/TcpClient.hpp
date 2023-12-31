/*
** EPITECH PROJECT, 2023
** TcpClient.hpp
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <asio.hpp>
#include <iostream>

namespace RType::Client
{
    class TcpClient
    {
      public:
        TcpClient(asio::io_context &IOContext, asio::ip::tcp::endpoint &serverEndpoint);
        ~TcpClient();

        /// @brief Connect to the TCP server
        void run();
        bool &getTcpStatus();

      protected:
      private:
        /// @brief Restart the timeout
        void handleTimeout();

        /// @brief Handle the write operation to the server
        /// @param error checked if occured
        void handleWrite(const asio::error_code &error);

        /// @brief Handle the input operation from the stdin
        /// @param error checked if occured
        /// @param recvBytes corresponding the number bytes receive from the
        /// server
        void handleInput(const asio::error_code &error, std::size_t recvBytes);

        bool _tcpRunning;
        asio::io_context &_IOContext;
        asio::ip::tcp::endpoint &_serverEndpoint;
        asio::ip::tcp::socket _socket;
        asio::streambuf _inputBuffer;
    };
} // namespace RType::Client

#endif /* !TCPCLIENT_HPP_ */
