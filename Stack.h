#pragma once
#include "StackImpl.h"
#include "VectorStack.h"
#include "LinkedListStack.h"

enum class StackType {
    LinkedList = 0,
    Vector
};

class Stack {
public:
    Stack(StackType type = StackType::Vector);

    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;
    virtual ~Stack();

    virtual void push(ValueType value) { _impl->push(value); }
    virtual void pop() { _impl->pop(); }
    virtual ValueType top() const { return _impl->top(); }
    virtual size_t size() const noexcept { return _impl->size(); }
    virtual bool empty() const noexcept { return _impl->empty(); }

private:
    StackImpl* _impl;
    StackType _type;
};

Stack::Stack(StackType type) {
    _type = type;
    if (_type == StackType::Vector) {
        _impl = new VectorStack();
    }
    else if (_type == StackType::LinkedList) {
        _impl = new LinkedListStack();
    }
}

Stack::Stack(const Stack& other) {
    _type = other._type;
    if (_type == StackType::Vector) {
        _impl = new VectorStack();
    }
    else if (_type == StackType::LinkedList) {
        _impl = new LinkedListStack();
    }

    size_t size = other.size();
    ValueType* data = new ValueType[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other._impl->top();
        other._impl->pop();
    }
    for (long long i = size - 1; i  > -1; --i) {
        push(data[i]);
        other._impl->push(data[i]);
    }
}

Stack::Stack(Stack&& other) noexcept {
    _impl = other._impl;
    _type = other._type;
    other._impl = nullptr;
}

Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        delete _impl;

        _type = other._type;
        if (_type == StackType::Vector) {
            _impl = new VectorStack();
        } else if (_type == StackType::LinkedList) {
            _impl = new LinkedListStack();
        }

        size_t size = other.size();
        ValueType *data = new ValueType[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other._impl->top();
            other._impl->pop();
        }
        for (long long i = size - 1; i  > -1; --i) {
            push(data[i]);
            other._impl->push(data[i]);
        }
    }
    return *this;
}

Stack& Stack::operator=(Stack&& other) noexcept {
    std::swap(_impl, other._impl);
    std::swap(_type, other._type);
    return *this;
}

Stack::~Stack() {
    delete _impl;
}