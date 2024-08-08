#include "Arraytemplate.h"
#include <cstddef>
#include <exception>
#include <iostream>

// Конструктор по умолчанию
template <typename D>
IntegerArray<D>::IntegerArray() : data(nullptr), size(0) {}

// Параметризованный конструктор
template <typename D>
IntegerArray<D>::IntegerArray(size_t size) : data(new D[size]), size(size)
{
    if (size < 0) throw bad_length();
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = 0;
    }
}

// Деструктор
template <typename D>
IntegerArray<D>::~IntegerArray()
{
    delete[] data;
}

// Перегрузка оператора []
template <typename D>
D& IntegerArray<D>::operator[](size_t index)
{
    if (index >= size) throw bad_range();
    return data[index];
}

template <typename D>
const D& IntegerArray<D>::operator[](size_t index) const
{
    if (index >= size) throw bad_range();
    return data[index];
}

// Изменение размера массива
template <typename D>
void IntegerArray<D>::resize(size_t newSize)
{
    if (newSize < 0) throw bad_length();

    D* newData = new D[newSize];
    size_t minSize = (size < newSize) ? size : newSize;

    for (size_t i = 0; i < minSize; ++i)
    {
        newData[i] = data[i];
    }
    for (size_t i = minSize; i < newSize; ++i)
    {
        newData[i] = 0;
    }

    delete[] data;
    data = newData;
    size = newSize;
}

// Вставка элемента
template <typename D>
void IntegerArray<D>::insert(size_t index, D value)
{
    if (index > size) throw bad_range();

    resize(size + 1);
    for (size_t i = size - 1; i > index; --i)
    {
        data[i] = data[i - 1];
    }
    data[index] = value;
}

// Удаление элемента
template <typename D>
void IntegerArray<D>::remove(size_t index)
{
    if (index >= size) throw bad_range();

    for (size_t i = index; i < size - 1; ++i)
    {
        data[i] = data[i + 1];
    }
    resize(size - 1);
}

// Получение размера массива
template <typename D>
size_t IntegerArray<D>::getSize() const
{
    return size;
}

// Конструктор копирования
template <typename D>
IntegerArray<D>::IntegerArray(const IntegerArray& other) : data(new D[other.size]), size(other.size)
{
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }
}

// Перегрузка оператора присваивания
template <typename D>
IntegerArray<D>& IntegerArray<D>::operator=(const IntegerArray& other)
{
    if (this == &other) return *this;

    delete[] data;
    size = other.size;
    data = new D[size];
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i];
    }

    return *this;
}

// Конструктор перемещения
template <typename D>
IntegerArray<D>::IntegerArray(IntegerArray&& other) noexcept : data(other.data), size(other.size)
{
    other.data = nullptr;
    other.size = 0;
}

// Перегрузка оператора присваивания с перемещением
template <typename D>
IntegerArray<D>& IntegerArray<D>::operator=(IntegerArray&& other) noexcept
{
    if (this == &other) return *this;

    delete[] data;
    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;

    return *this;
}

// Явное инстанцирование шаблонов
template class IntegerArray<int>;
template class IntegerArray<unsigned long>;
