/*
** EPITECH PROJECT, 2023
** Serialization.hpp
** File description:
** Serialization
*/

#ifndef SERIALIZATION_HPP_
#define SERIALIZATION_HPP_

#include <asio.hpp>
#include <vector>
#include <cstddef>
#include <cstring>

namespace Serialization
{
    template <typename Data>
    std::vector<std::byte> serializeData(Data data)
    {
        std::vector<std::byte> byteArray(sizeof(data));

        byteArray.reserve(sizeof(data));
        std::memcpy(byteArray.data(), &data, sizeof(data));
        return byteArray;
    }

    template <typename Data>
    Data deserializeData(asio::streambuf::mutable_buffers_type &buffer, std::size_t size)
    {
        Data data;

        std::memcpy(&data, buffer.data(), size);
        return data;
    }

    inline std::vector<uint8_t> deserializeData(asio::streambuf::mutable_buffers_type &buffer, std::size_t size)
    {
        std::vector<uint8_t> byteArray(size);

        byteArray.reserve(size);
        std::memcpy(byteArray.data(), buffer.data(), size);
        return byteArray;
    }
}; // namespace Serialization

#endif /* !SERIALIZATION_HPP_ */
