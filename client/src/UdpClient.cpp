/*
** EPITECH PROJECT, 2023
** UdpClient.cpp
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

Network::UdpClient::UdpClient(asio::io_context &IOContext,
                              asio::ip::udp::endpoint &serverEndpoint)
    : _socket(IOContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
      _serverEndpoint(serverEndpoint), _IOContext(IOContext),
      _is(&_streamBuffer),
      _isHeader(&_streamBufferHeader),
      _buffer(_streamBufferHeader.prepare(52))
{
    run();
}

Network::UdpClient::~UdpClient() { _socket.close(); }

void Network::UdpClient::handleReceive(const asio::error_code &error,
                                       std::size_t recvBytes)
{
    if (!error) {
        std::cout << "Size : " << recvBytes << std::endl;
        if (recvBytes != 52) {
            std::cout << "PETE" << std::endl;
            _streamBufferHeader.consume(recvBytes);
            return;
        }
        _streamBufferHeader.commit(recvBytes);
        struct rtype::HeaderDataPacket header;
        boost::archive::binary_iarchive binaryArchive(_isHeader);
        binaryArchive >> header;
        _streamBufferHeader.consume(recvBytes);
        if (header.magicNumber == rtype::MAGIC_NUMBER) {
            std::cout << "Good header, can read data" << std::endl;
            readData(header);
        }
    } else {
        std::cerr << "Error : " << error.message() << std::endl;
    }
    handleTimeout();
}

void Network::UdpClient::handleTimeout()
{
    asio::steady_timer timeout(_IOContext);
    timeout.expires_from_now(std::chrono::seconds(5));
    timeout.async_wait([&](const asio::error_code &error) {
        if (!error) {
            _socket.cancel();
            std::cerr << "Timeout on response from server !" << std::endl;
        }
    });
    receive();
}

void Network::UdpClient::readData(const struct rtype::HeaderDataPacket header)
{
    _buffer = _streamBuffer.prepare(header.payloadSize);
    _socket.async_receive_from(
        _buffer, _serverEndpoint,
        [&](const asio::error_code &error, std::size_t recvBytes) {
            if (error)
                return;
            _streamBuffer.commit(recvBytes);
            boost::archive::binary_iarchive binaryArchive(_is);
            std::string message;
            binaryArchive >> message;
            std::cout << message << std::endl;
            if (message == "Server down") {
                _socket.close();
                _IOContext.stop();
            }
            _streamBuffer.consume(recvBytes);
        });
}

void Network::UdpClient::receive()
{
    _buffer = _streamBufferHeader.prepare(52);
    _socket.async_receive_from(_buffer, _serverEndpoint,
                               std::bind(&Network::UdpClient::handleReceive,
                                         this, std::placeholders::_1,
                                         std::placeholders::_2));
}

void Network::UdpClient::run()
{
    std::string buff;
    std::array<char, 1> data;
    std::copy(buff.begin(), buff.end(), data.begin());
    _socket.async_send_to(asio::buffer(data, buff.size()), _serverEndpoint,
                          std::bind(&Network::UdpClient::receive, this));
}
