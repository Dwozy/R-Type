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
      _IOContext(IOContext),
      _is(&_streamBuffer)
{
    run();
}

UdpClient::~UdpClient()
{
    _socket.close();
}

void UdpClient::handleReceive(const boost::system::error_code &error, std::size_t recvBytes)
{
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
}

void UdpClient::readData(const struct rtype::HeaderDataPacket header)
{
    return;
}

void UdpClient::receive()
{
    boost::asio::streambuf::mutable_buffers_type bufs = _streamBuffer.prepare(67);
    _socket.async_receive_from(bufs, _serverEndpoint,
        [&] (const boost::system::error_code &error, std::size_t recvBytes) {
            if (!error) {
                std::cout << "Size : " << recvBytes << std::endl;
                if (recvBytes != 67) {
                    std::cout << "PETE" << std::endl;
                    receive();
                }
                _streamBuffer.commit(recvBytes);
                struct rtype::HeaderDataPacket header;
                boost::archive::binary_iarchive binaryArchive(_is);
                binaryArchive >> header;
                std::string buff = "";
                _streamBuffer.consume(recvBytes);
                if (header.signature == "R-TYPE") {
                    std::cout << "Good header, can read data" << std::endl;
                    readData(header);
                }
                if (buff == "Server down") {
                    _socket.close();
                    _IOContext.stop();
                } else
                    std::cout << buff << std::endl;;
            } else {
                std::cerr << "Error : " << error.message() << std::endl;
            }
            receive();
        });
}

void UdpClient::run()
{
    std::string buff;
    std::array<char, 1> data;
    std::copy(buff.begin(), buff.end(), data.begin());
    _socket.async_send_to(boost::asio::buffer(data, buff.size()), _serverEndpoint,
        boost::bind(&UdpClient::receive, this));
}
