#pragma once
#include "StackImpl.h"
#include "VectorStack.h"
#include "LinkedListStack.h"

enum class StackType {
    LinkedList = 0,
    Vector
};

template<class T>
class Stack {
public:
    Stack(StackType type = StackType::Vector);

    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other) noexcept;
    Stack& operator=(const Stack<T>& other);
    Stack& operator=(Stack<T>&& other) noexcept;
    ~Stack();

    void push(T value);
    void pop();
    T& top() const;
    size_t size() const noexcept;
    bool empty() const noexcept;

private:
    StackImpl<T>* _impl;
    StackType _type;
};

template<class T>
Stack<T>::Stack(StackType type) {
    _type = type;
    if (_type == StackType::Vector) {
        _impl = new VectorStack<T>();
    }
    else if (_type == StackType::LinkedList) {
        _impl = new LinkedListStack<T>();
    }
}

template<class T>
Stack<T>::Stack(const Stack<T>& other) {
    _type = other._type;
    if (_type == StackType::Vector) {
        _impl = new VectorStack<T>();
    }
    else if (_type == StackType::LinkedList) {
        _impl = new LinkedListStack<T>();
    }

    size_t size = other.size();
    T* data = new T[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other._impl->top();
        other._impl->pop();
    }
    for (long long i = size - 1; i  > -1; --i) {
        push(data[i]);
        other._impl->push(data[i]);
    }
}

template<class T>
Stack<T>::Stack(Stack<T>&& other) noexcept {
    _impl = other._impl;
    _type = other._type;
    other._impl = nullptr;
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        delete _impl;

        _type = other._type;
        if (_type == StackType::Vector) {
            _impl = new VectorStack<T>();
        }
        else if (_type == StackType::LinkedList) {
            _impl = new LinkedListStack<T>();
        }

        size_t size = other.size();
        T *data = new T[size];
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

template<class T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
    std::swap(_impl, other._impl);
    std::swap(_type, other._type);
    return *this;
}

template<class T>
Stack<T>::~Stack() {
    delete _impl;
}

template<class T>
void Stack<T>::push(T value) {
    _impl->push(value);
}

template<class T>
void Stack<T>::pop() {
    _impl->pop();
}

template<class T>
T& Stack<T>::top() const {
    return _impl->top();
}

template<class T>
size_t Stack<T>::size() const noexcept {
    return _impl->size();
}

template<class T>
bool Stack<T>::empty() const noexcept {
    return _impl->empty();
}