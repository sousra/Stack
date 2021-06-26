#pragma once
#include "StackImpl.h"
#include "SLL.h"

class LinkedListStack : public StackImpl {
public:
    LinkedListStack() { _container =  SLL(); }

    void push(ValueType value) override { _container.pushFront(value); }
    void pop() override { _container.popFront(); }
    ValueType top() const override { return _container.front(); }
    size_t size() const noexcept override { return _container.size(); }
    bool empty() const noexcept override { return !size(); }

private:
    SLL _container;
};
