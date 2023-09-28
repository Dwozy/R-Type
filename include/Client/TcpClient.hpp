/*
** EPITECH PROJECT, 2023
** TcpClient.hpp
** File description:
** TcpClient
*/

#ifndef TCPCLIENT_HPP_
    #define TCPCLIENT_HPP_

    #include <iostream>
    #include <boost/asio.hpp>
    #include <boost/bind/bind.hpp>

class TcpClient {
    public:
        TcpClient(boost::asio::io_context &IOContext, boost::asio::ip::tcp::endpoint &serverEndpoint);
        ~TcpClient();

    protected:
    private:
        boost::asio::io_context &_IOContext;
        boost::asio::ip::tcp::endpoint &_serverEndpoint;
        boost::asio::ip::tcp::socket _socket;
        boost::asio::posix::stream_descriptor _input;
        boost::asio::streambuf _inputBuffer;

        /// @brief Connect to the TCP server
        void run();

        /// @brief Restart the timeout
        void handleTimeout();

        /// @brief Handle the write operation to the server
        /// @param error checked if occured
        void handleWrite(const boost::system::error_code &error);

        /// @brief Handle the input operation from the stdin
        /// @param error checked if occured
        /// @param recvBytes corresponding the number bytes receive from the server
        void handleInput(const boost::system::error_code &error, std::size_t recvBytes);

};

#endif /* !TCPCLIENT_HPP_ */
