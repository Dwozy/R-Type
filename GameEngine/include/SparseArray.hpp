/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
#define SPARSEARRAY_HPP_
#include <memory>
#include <optional>
#include <vector>
#include "Error.hpp"

/// @brief Array which can have empty indexes.
/// @tparam Component Type of the component in the array.
template <typename Component>
class SparseArray
{
  public:
    /// @brief Type of the array wrap in an optional.
    using valueType = std::optional<Component>;
    /// @brief Reference to valueType.
    using referenceType = valueType &;
    /// @brief Constant reference to valueType.
    using constReferenceType = const valueType &;
    /// @brief Type of the container, which is a a vector storing a valueType.
    using container = std::vector<valueType>;

    /// @brief Type of the size of the container.
    using sizeType = typename container::size_type;

    /// @brief Type of the container's iterator.
    using iterator = typename container::iterator;
    /// @brief Constant type of the container's iterator.
    using constIterator = typename container::const_iterator;

    /// @brief SparseArray's constructor.
    SparseArray(){};
    /// @brief Copy constructor for the SparseArray.
    /// @param sparseArray SparseArray to copy.
    SparseArray(const SparseArray &sparseArray) : _data(sparseArray._data){};

    ~SparseArray() = default;

    /// @brief Overload for the copy assignement operator.
    /// @param sparseArray SparseArray to copy.
    /// @return A reference to the SparseArray.
    SparseArray &operator=(const SparseArray &sparseArray)
    {
        _data = sparseArray._data;
        return *this;
    };
    /// @brief Overload for the move assignment operator.
    /// @param sparseArray SparseArray to move.
    /// @return A reference to the SparseArray.
    SparseArray &operator=(SparseArray &&sparseArray) noexcept
    {
        _data = sparseArray._data;
        return *this;
    };

    /// @brief Overload for the bracket operator.
    /// @param idx Index to get the value at.
    /// @return Reference to the value at the index.
    referenceType operator[](std::size_t idx) { return _data[idx]; };
    /// @brief Overload for the bracket operator.
    /// @param idx Index to get the value at.
    /// @return Constant reference to the value at the index.
    constReferenceType operator[](std::size_t idx) const { return _data[idx]; };

    /// @brief Getter for the begin iterator.
    /// @return An iterator at the begining of the array.
    iterator begin() { return _data.begin(); };
    /// @brief Getter for the begin iterator.
    /// @return A constant iterator at the begining of the array.
    constIterator begin() const { return _data.begin(); };
    /// @brief Getter for the begin iterator.
    /// @return A constant iterator at the begining of the array.
    constIterator cbegin() const { return _data.cbegin(); };

    /// @brief Getter for the end iterator.
    /// @return An iterator at the end of the array.
    iterator end() { return _data.end(); };
    /// @brief Getter for the end iterator.
    /// @return A constant iterator at the end of the array.
    constIterator end() const { return _data.end(); };
    /// @brief Getter for the end iterator.
    /// @return A constant iterator at the end of the array.
    constIterator cend() const { return _data.cend(); };

    /// @brief Getter for the array's size.
    /// @return The size of the array.
    sizeType size() const { return _data.size(); };

    /// @brief Insert a copy of the component at the position specified. Will resize the array if the position is bigger
    /// than the size of the array.
    /// @param pos Position to insert the component at.
    /// @param component Copy of the component to insert.
    /// @return A reference to the inserted component.
    referenceType insert_at(sizeType pos, const Component &component)
    {
        if (_data.size() < pos + 1)
            _data.resize(pos + 1);
        _data[pos] = component;
        return _data[pos];
    };
    /// @brief Insert the component at the position specified, the component will be moved in. Will resize the array if
    /// the position is bigger than the size of the array.
    /// @param pos Position to insert the component at.
    /// @param component Moved component to insert.
    /// @return A reference to the inserted component.
    referenceType insert_at(sizeType pos, Component &&component)
    {
        if (_data.size() < pos + 1)
            _data.resize(pos + 1);
        _data[pos] = component;
        return _data[pos];
    };

    /// @brief Creates the component at the specified position.
    /// @param pos Position to create the component at.
    /// @return A reference to the created component.
    referenceType emplace_at(sizeType pos)
    {
        auto &ret = insert_at(pos, Component());
        return ret;
    };
    /// @brief Creates components at the specified positions
    /// @tparam ...Params Variadic template of the type of the positions
    /// @param pos First position to create the component.
    /// @param ...params Variadic parameter of the positions to insert at.
    /// @return A reference to the first component created.
    template <class... Params>
    referenceType emplace_at(sizeType pos, Params &&...params)
    {
        auto &ret = insert_at(pos, Component());

        emplace_at(params...);
        return ret;
    };

    /// @brief Removes the component at the specified position.
    /// @param pos Position at which to remove the component.
    void erase(sizeType pos)
    {
        if (_data.size() > pos && _data[pos].has_value())
            _data[pos].reset();
    };
    /// @brief Getter for the index of the component given. The component needs to be in the array.
    /// @param val Component from which to get the index.
    /// @return The index of the component.
    sizeType getIndex(const valueType &val) const
    {
        for (sizeType pos = 0; pos < _data.size(); pos++) {
            if (std::addressof(_data[pos]) == std::addressof(val))
                return pos;
        }
        throw Error::ComponentNotInsertedError();
    };

    /// @brief Resize the array.
    /// @param count Size to resize the array.
    void resize(const std::size_t &count) { _data.resize(count); }

  private:
    /// @brief Container of the components.
    container _data;
};

#endif /* !SPARSEARRAY_HPP_ */
