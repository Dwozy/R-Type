/*
** EPITECH PROJECT, 2023
** UdpClient.cpp
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

UdpClient::UdpClient(boost::asio::io_context &IOContext, boost::asio::ip::udp::endpoint &serverEndpoint)
    : _socket(IOContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
      _serverEndpoint(serverEndpoint),
      _IOContext(IOContext)
{
    run();
}

UdpClient::~UdpClient()
{
    _socket.close();
}

void UdpClient::handleReceive(const boost::system::error_code &error, std::size_t recvBytes,
    boost::asio::deadline_timer &timeout)
{
    timeout.cancel();
    if (!error) {
        std::string buff = std::string(_readBuffer.begin(), _readBuffer.begin() + recvBytes);
        if (buff == "Server down") {
            _socket.close();
            _IOContext.stop();
        } else
            std::cout << buff;
    } else {
        std::cerr << "Error : " << error.message() << std::endl;
    }
    handleTimeout();
}

void UdpClient::handleTimeout()
{
    boost::asio::deadline_timer timeout(_IOContext);
    timeout.expires_from_now(boost::posix_time::seconds(5));
    timeout.async_wait([&] (const boost::system::error_code &error) {
        if (!error) {
            _socket.cancel();
            std::cerr << "Timeout on response from server !" << std::endl;
        }
    });
    receive(timeout);
}

void UdpClient::receive(boost::asio::deadline_timer &timeout)
{
    _socket.async_receive_from(boost::asio::buffer(_readBuffer, 1024), _serverEndpoint,
        boost::bind(&UdpClient::handleReceive, this, boost::placeholders::_1, boost::placeholders::_2, std::ref(timeout)));
}

void UdpClient::run()
{
    std::string buff;
    std::array<char, 1> data;
    std::copy(buff.begin(), buff.end(), data.begin());
    _socket.async_send_to(boost::asio::buffer(data, buff.size()), _serverEndpoint,
        boost::bind(&UdpClient::handleTimeout, this));
}
