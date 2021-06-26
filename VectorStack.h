#pragma once
#include "StackImpl.h"
#include "MyVector.h"

template<class T>
class VectorStack : public StackImpl<T> {
public:
    void push(T value) override;
    void pop() override;
    T& top() const override;
    size_t size() const noexcept override;
    bool empty() const noexcept override;

private:
    MyVector<T> _container;
};

template<class T>
void VectorStack<T>::push(T value) {
    _container.pushBack(value);
}

template<class T>
void VectorStack<T>::pop() {
    _container.popBack();
}

template<class T>
T& VectorStack<T>::top() const {
    return _container.back();
}

template<class T>
size_t VectorStack<T>::size() const noexcept {
    return _container.size();
}

template<class T>
bool VectorStack<T>::empty() const noexcept {
    return !size();
}