#pragma once
#include "StackImpl.h"
#include "MyVector.h"

class VectorStack : public StackImpl {
public:
    VectorStack() { _container =  MyVector(); }
    VectorStack(const VectorStack& other) { }

    void push(ValueType value) override { _container.pushBack(value); }
    void pop() override { _container.popBack(); }
    ValueType top() const override { return _container.back(); }
    size_t size() const noexcept override { return _container.size(); }
    bool empty() const noexcept override { return !size(); }

private:
    MyVector _container;
};