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
    /// @brief Template to serialize the data
    /// @tparam Data corresponding of the type of data
    /// @param data that need to be serialize
    /// @return list of bytes (corresponding the data)
    template <typename Data>
    std::vector<std::byte> serializeData(Data data, std::size_t size)
    {
        std::vector<std::byte> byteArray(size);

        byteArray.reserve(size);
        std::memmove(byteArray.data(), &data, size);
        return byteArray;
    }
    /// @brief Template to deserialize the data
    /// @tparam Data corresponding of the type of data
    /// @param buffer that we will retrieve the data
    /// @param size of the data
    /// @return the data
    template <typename Data>
    Data deserializeData(asio::streambuf &buffer, std::size_t size)
    {
        Data data;

        std::memcpy(&data, buffer.data().data(), size);
        return data;
    }
    /// @brief Retrieve the data in a list of bytes
    /// @param buffer that we will retrieve the data
    /// @param size of the data
    /// @return list of bytes
    inline std::vector<uint8_t> deserializeData(asio::streambuf &buffer, std::size_t size)
    {
        std::vector<uint8_t> byteArray(size);

        byteArray.reserve(size);
        std::memcpy(byteArray.data(), buffer.data().data(), size);
        return byteArray;
    }
}; // namespace Serialization

#endif /* !SERIALIZATION_HPP_ */
