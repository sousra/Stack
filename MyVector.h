#pragma once
#include <iostream>
#include <exception>

enum class ResizeStrategy {
    Additive,
    Multiplicative
};

template<class T>
class MyVector {
public:
    class Iterator {
    public:
        Iterator() = default;
        Iterator(T* ptr);

        T& operator*();

        Iterator& operator++();
        Iterator& operator--();

        Iterator operator++(int);
        Iterator operator--(int);

        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);

    private:
        T* _ptr;
    };
    Iterator begin();
    Iterator end();


public:
    MyVector(ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);
    MyVector(size_t size,
             ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);
    MyVector(size_t size,
             const T& value,
             ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);
    MyVector(size_t size,
             const T* rawVector,
             ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);

    MyVector(const MyVector<T>& other);
    MyVector(MyVector<T>&& other) noexcept;
    MyVector& operator=(const MyVector<T>& other);
    MyVector& operator=(MyVector<T>&& other) noexcept;
    ~MyVector();

    T& at(size_t idx);
    const T& at(size_t idx) const;
    T& operator[](const size_t idx);
    const T& operator[](const size_t idx) const;

    // Если размер вставляемого больше чем capacity +=/*= coef,
    // то capacity = размер вставляемого + size
    void insert(Iterator pos, const T& value);
    void insert(size_t idx, const T& value);
    void pushBack(const T& value);

    // Очистить вектор без изменения capacity
    void clear() noexcept;

    void erase(Iterator pos, size_t len = 1);
    void erase(size_t idx, size_t len = 1);
    void popBack();

    // Задать size
    // Если новый size больше старого - записываем в новые элементы value
    // Если меньше - обрезаем вектор
    void resize(size_t newSize, const T& value = T());

    // Задать capacity
    // Уменьшать capacity нельзя
    void reserve(size_t capacity);

    // Сделать capacity равным size
    void shrinkToFit();


    T& front() const noexcept;
    T& back() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    float loadFactor() const noexcept;

    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть end
    Iterator find(const T& value, bool isBegin = true);

private:
    T* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _resizeStrategy;
    float _coef;
};


template<class T>
MyVector<T>::MyVector(ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = 0;
    _data = nullptr;
    _capacity = 0;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
}

template<class T>
MyVector<T>::MyVector(size_t size,
                   ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = size;
    _capacity = size;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
    _data = new T[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = T();
    }
}

template<class T>
MyVector<T>::MyVector(size_t size,
                   const T& value,
                   ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = size;
    _capacity = size;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
    _data = new T[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = value;
    }
}

template<class T>
MyVector<T>::MyVector(size_t size,
                   const T* rawVector,
                   ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = size;
    _capacity = size;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = rawVector[i];
    }
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _resizeStrategy = other._resizeStrategy;
    _coef = other._coef;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

template<class T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept {
    _size = other._size;
    _capacity = other._capacity;
    _resizeStrategy = other._resizeStrategy;
    _coef = other._coef;
    _data = other._data;
    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
    if (this != &other) {
        _size = other._size;
        _capacity = other._capacity;
        _resizeStrategy = other._resizeStrategy;
        _coef = other._coef;
        delete[] _data;
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _resizeStrategy = other._resizeStrategy;
        _coef = other._coef;
        _data = other._data;
        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;
    }
    return *this;
}

template<class T>
MyVector<T>::~MyVector() {
    delete[] _data;
}

template<class T>
T& MyVector<T>::at(size_t idx) {
    if (idx < 0 || idx >= _size) {
        throw std::out_of_range("Invalid index");
    }
    return _data[idx];
}

template<class T>
const T& MyVector<T>::at(size_t idx) const {
    if (idx < 0 || idx >= _size) {
        throw std::out_of_range("Invalid index");
    }
    return _data[idx];
}

template<class T>
T& MyVector<T>::operator[](size_t idx) {
    return _data[idx];
}

template<class T>
const T& MyVector<T>::operator[](size_t idx) const {
    return _data[idx];
}

template<class T>
void MyVector<T>::insert(Iterator pos, const T& value) {
    MyVector::Iterator it = begin();
    size_t idx = 0;
    while (it != pos) {
        ++it;
        ++idx;
    }
    insert(idx, value);
}

template<class T>
void MyVector<T>::insert(size_t idx, const T& value) {
    if (idx < 0 || idx > _size) {
        throw std::out_of_range("Invalid index");
    }
    if (_size + 1 > _capacity) {
        size_t newCapacity;
        if (_resizeStrategy == ResizeStrategy::Additive) {
            newCapacity = (_capacity + _coef < _size + 1) ? (_size + 1) : (_capacity + _coef);
        }
        else if (_resizeStrategy == ResizeStrategy::Multiplicative) {
            newCapacity = (_capacity * _coef < _size + 1) ? (_size + 1) : (_capacity * _coef);
        }
        reserve(newCapacity);
    }
    ++_size;
    for (size_t i = _size - 1; i > idx; --i) {
        _data[i] = _data[i - 1];
    }
    _data[idx] = value;
}

template<class T>
void MyVector<T>::pushBack(const T& value) {
    insert(_size, value);
}

template<class T>
void MyVector<T>::clear() noexcept {
    _size = 0;
}

template<class T>
void MyVector<T>::erase(Iterator pos, size_t len) {
    MyVector::Iterator it = begin();
    size_t idx = 0;
    while (it != pos) {
        ++it;
        ++idx;
    }
    erase(idx, len);
}

template<class T>
void MyVector<T>::erase(size_t idx, size_t len) {
    if (idx < 0 || idx >= _size) {
        throw std::out_of_range("Invalid index");
    }
    len = (len > _size - idx) ? _size - idx : len;
    for (; idx < _size - len; ++idx) {
        _data[idx] = _data[idx + len];
    }
    _size -= len;
}

template<class T>
void MyVector<T>::popBack() {
    if (_size == 0) {
        throw std::logic_error("Empty vector");
    }
    --_size;
}

template<class T>
void MyVector<T>::resize(size_t newSize, const T& value) {
    reserve(newSize);
    for (size_t i = _size; i < newSize; ++i) {
        _data[i] = value;
    }
    _size = newSize;
    /*
    if (newSize <= _size) {
        _size = newSize;
    }
    else if (newSize <= _capacity) {
        for (size_t i = _size; i < newSize; ++i) {
            _data[i] = value;
        }
        _size = newSize;
    }
    else {
        reserve(newSize);
        for (size_t i = _size; i < newSize; ++i) {
            _data[i] = value;
        }
        _size = newSize;
    }
    */
}

template<class T>
void MyVector<T>::reserve(size_t capacity) {
    if (capacity > _capacity) {
        _capacity = capacity;
        T* temp = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
}

template<class T>
void MyVector<T>::shrinkToFit() {
    if (_capacity > _size) {
        _capacity = _size;
        T* temp = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
}

template<class T>
T& MyVector<T>::front() const noexcept {
    if (_size == 0) {
        throw std::logic_error("Empty vector");
    }
    return _data[0];
}

template<class T>
T& MyVector<T>::back() const noexcept {
    if (_size == 0) {
        throw std::logic_error("Empty vector");
    }
    return _data[_size - 1];
}

template<class T>
size_t MyVector<T>::size() const noexcept {
    return _size;
}

template<class T>
size_t MyVector<T>::capacity() const noexcept {
    return _capacity;
}

template<class T>
float MyVector<T>::loadFactor() const noexcept {
    return (float) _size / _capacity;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::find(const T& value, bool isBegin)  {
    MyVector::Iterator it = begin();
    MyVector::Iterator res = end();
    while (it != end()) {
        if (*it == value) {
            res = it;
            if (isBegin == true) {
                return res;
            }
        }
        ++it;
    }
    return res;

}

template<class T>
MyVector<T>::Iterator::Iterator(T* ptr) {
    _ptr = ptr;
}

template<class T>
T& MyVector<T>::Iterator::operator*() {
    return  *_ptr;
}

template<class T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator++() {
    ++_ptr;
    return *this;
}

template<class T>
typename MyVector<T>::Iterator& MyVector<T>::Iterator::operator--() {
    --_ptr;
    return *this;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

template<class T>
bool MyVector<T>::Iterator::operator==(const Iterator& other) {
    return _ptr == other._ptr;
}

template<class T>
bool MyVector<T>::Iterator::operator!=(const Iterator& other) {
    return !(*this == other);
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::begin() {
    return Iterator(&_data[0]);
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::end() {
    return Iterator(&_data[_size]);
}