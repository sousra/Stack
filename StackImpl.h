#pragma once

template<class T>
class StackImpl {
public:
    virtual void push(T value) = 0;
    virtual void pop() = 0;
    virtual T& top() const = 0;
    virtual size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;
};