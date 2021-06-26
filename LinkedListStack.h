#pragma once
#include "StackImpl.h"
#include "SLL.h"

template<class T>
class LinkedListStack : public StackImpl<T> {
public:
    void push(T value) override;
    void pop() override;
    T& top() const override;
    size_t size() const noexcept override;
    bool empty() const noexcept override;

private:
    SLL<T> _container;
};

template<class T>
void LinkedListStack<T>::push(T value) {
    _container.pushFront(value);
}

template<class T>
void LinkedListStack<T>::pop() {
    _container.popFront();
}

template<class T>
T& LinkedListStack<T>::top() const {
    return _container.front();
}

template<class T>
size_t LinkedListStack<T>::size() const noexcept {
    return _container.size();
}

template<class T>
bool LinkedListStack<T>::empty() const noexcept {
    return !size();
}