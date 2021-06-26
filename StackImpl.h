#pragma once

using ValueType = int;

class StackImpl {
public:
    virtual void push(ValueType value) = 0;
    virtual void pop() = 0;
    virtual ValueType top() const = 0;
    virtual size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;
};