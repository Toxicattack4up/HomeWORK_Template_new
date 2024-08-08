#ifndef ARRAYTEMPLATE_H
#define ARRAYTEMPLATE_H

#include <cstddef>
#include <exception>

class bad_range : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Индекс вне диапазона";
    }
};

class bad_length : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Неверная длина";
    }
};

template <typename D>
class IntegerArray
{
private:
    D* data;
    size_t size;

public:
    IntegerArray();
    explicit IntegerArray(size_t size);
    ~IntegerArray();

    D& operator[](size_t index);
    const D& operator[](size_t index) const;

    void resize(size_t newSize);
    void insert(size_t index, D value);
    void remove(size_t index);

    size_t getSize() const;

    IntegerArray(const IntegerArray& other);
    IntegerArray& operator=(const IntegerArray& other);
    IntegerArray(IntegerArray&& other) noexcept;
    IntegerArray& operator=(IntegerArray&& other) noexcept;
};

#include "Arraytemplate.cpp"

#endif // ARRAYTEMPLATE_H
