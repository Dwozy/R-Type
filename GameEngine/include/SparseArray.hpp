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

template <typename Component> class SparseArray
{
  public:
    using valueType = std::optional<Component>;
    using referenceType = valueType &;
    using constReferenceType = const valueType &;
    using container = std::vector<valueType>;
    using sizeType = typename container::size_type;

    using iterator = typename container::iterator;
    using constIterator = typename container::const_iterator;

    SparseArray(){};

    SparseArray(const SparseArray &sparseArray) : _data(sparseArray._data){};
    SparseArray(SparseArray &&sparseArray) noexcept
        : _data(sparseArray._data){};

    ~SparseArray(){};

    SparseArray &operator=(const SparseArray &sparseArray)
    {
        _data = sparseArray._data;
    };
    SparseArray &operator=(SparseArray &&sparseArray) noexcept
    {
        _data = sparseArray._data;
    };

    referenceType operator[](std::size_t idx) { return _data[idx]; };
    constReferenceType operator[](std::size_t idx) const { return _data[idx]; };

    iterator begin() { return _data.begin(); };
    constIterator begin() const { return _data.begin(); };
    constIterator cbegin() const { return _data.cbegin(); };

    iterator end() { return _data.end(); };
    constIterator end() const { return _data.end(); };
    constIterator cend() const { return _data.cend(); };

    sizeType size() const { return _data.size(); };

    referenceType insert_at(sizeType pos, const Component &component)
    {
        if (_data.size() < pos + 1)
            _data.resize(pos + 1);
        _data[pos] = component;
        return _data[pos];
    };
    referenceType insert_at(sizeType pos, Component &&component)
    {
        if (_data.size() < pos + 1)
            _data.resize(pos + 1);
        _data[pos] = component;
        return _data[pos];
    };

    referenceType emplace_at(sizeType pos)
    {
        auto &ret = insert_at(pos, Component());
        return ret;
    };
    template <class... Params>
    referenceType emplace_at(sizeType pos, Params &&...params)
    {
        auto &ret = insert_at(pos, Component());

        emplace_at(params...);
        return ret;
    };

    void erase(sizeType pos)
    {
        if (_data.size() > pos && _data[pos].has_value())
            _data[pos].reset();
    };
    sizeType getIndex(const valueType &val) const
    {
        for (sizeType pos = 0; pos < _data.size(); pos++) {
            if (std::addressof(_data[pos]) == std::addressof(val))
                return pos;
        }
        throw;
    };

  private:
    container _data;
};

#endif /* !SPARSEARRAY_HPP_ */
