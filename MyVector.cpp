#include <iostream>
#include <cassert>

#include "MyVector.h"

MyVector::MyVector(ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = 0;
    _data = nullptr;
    _capacity = 0;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
}

MyVector::MyVector(size_t size,
                   ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = size;
    _capacity = size;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
    _data = new ValueType[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = ValueType();
    }
}

MyVector::MyVector(size_t size,
                   const ValueType& value,
                   ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = size;
    _capacity = size;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
    _data = new ValueType[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = value;
    }
}

MyVector::MyVector(size_t size,
                   const ValueType* rawVector,
                   ResizeStrategy resizeStrategy,
                   float coef)
{
    _size = size;
    _capacity = size;
    _resizeStrategy = resizeStrategy;
    _coef = coef;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = rawVector[i];
    }
}

MyVector::MyVector(const MyVector& other) {
    _size = other._size;
    _capacity = other._capacity;
    _resizeStrategy = other._resizeStrategy;
    _coef = other._coef;
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

MyVector::MyVector(MyVector&& other) noexcept {
    _size = other._size;
    _capacity = other._capacity;
    _resizeStrategy = other._resizeStrategy;
    _coef = other._coef;
    _data = other._data;
    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;
}

MyVector& MyVector::operator=(const MyVector& other) {
    if (this != &other) {
        _size = other._size;
        _capacity = other._capacity;
        _resizeStrategy = other._resizeStrategy;
        _coef = other._coef;
        delete[] _data;
        _data = new ValueType[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

MyVector& MyVector::operator=(MyVector&& other) noexcept {
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
        return *this;
    }
}
MyVector::~MyVector() {
    delete[] _data;
}

ValueType& MyVector::at(size_t idx) {
    assert(idx < size());
    return _data[idx];
}

const ValueType& MyVector::at(size_t idx) const {
    assert(idx < size());
    return _data[idx];
}

ValueType& MyVector::operator[](size_t idx) {
    return _data[idx];
}

const ValueType& MyVector::operator[](size_t idx) const {
    return _data[idx];
}

void MyVector::insert(Iterator pos, const ValueType& value) {
    MyVector::Iterator it = begin();
    size_t idx = 0;
    while (it != pos) {
        ++it;
        ++idx;
    }
    insert(idx, value);
}

void MyVector::insert(size_t idx, const ValueType& value) {
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

void MyVector::pushBack(const ValueType& value) {
    insert(_size, value);
}

void MyVector::clear() noexcept {
    _size = 0;
}

void MyVector::erase(Iterator pos, size_t len) {
    MyVector::Iterator it = begin();
    size_t idx = 0;
    while (it != pos) {
        ++it;
        ++idx;
    }
    erase(idx, len);
}

void MyVector::erase(size_t idx, size_t len) {
    len = (len > _size - idx) ? _size - idx : len;
    for (; idx < _size - len; ++idx) {
        _data[idx] = _data[idx + len];
    }
    _size -= len;
}

void MyVector::popBack() {
    assert(_size > 0);
    --_size;
}

void MyVector::resize(size_t newSize, const ValueType& value) {
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

void MyVector::reserve(size_t capacity) {
    if (capacity > _capacity) {
        _capacity = capacity;
        ValueType* temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
}

void MyVector::shrinkToFit() {
    if (_capacity > _size) {
        _capacity = _size;
        ValueType* temp = new ValueType[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            temp[i] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
}

ValueType& MyVector::front() const noexcept {
    return _data[0];
}

ValueType& MyVector::back() const noexcept {
    return _data[_size - 1];
}


size_t MyVector::size() const noexcept {
    return _size;
}

size_t MyVector::capacity() const noexcept {
    return _capacity;
}

float MyVector::loadFactor() const noexcept {
    return (float) _size / _capacity;
}

MyVector::Iterator MyVector::find(const ValueType& value, bool isBegin)  {
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

MyVector::Iterator::Iterator(ValueType* ptr) {
    _ptr = ptr;
}

ValueType& MyVector::Iterator::operator*() {
    return  *_ptr;
}

MyVector::Iterator& MyVector::Iterator::operator++() {
    ++_ptr;
    return *this;
}

MyVector::Iterator& MyVector::Iterator::operator--() {
    --_ptr;
    return *this;
}

MyVector::Iterator MyVector::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

MyVector::Iterator MyVector::Iterator::operator--(int) {
    Iterator temp = *this;
    --(*this);
    return temp;
}

bool MyVector::Iterator::operator==(const Iterator& other) {
    return _ptr == other._ptr;
}

bool MyVector::Iterator::operator!=(const Iterator& other) {
    return !(*this == other);
}

MyVector::Iterator MyVector::begin() {
    return Iterator(&_data[0]);
}

MyVector::Iterator MyVector::end() {
    return Iterator(&_data[_size]);
}