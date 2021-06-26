#pragma once
#include <iostream>

using ValueType = int;

class SLL {
    class Node {
    public:
        Node(ValueType value) {
            _next = nullptr;
            _value = value;
        }
        Node* _next;
        ValueType _value;
    };
    Node* getNode(size_t idx);
public:
    class Iterator {
    public:
        Iterator(Node* ptr = nullptr) : _ptr(ptr) {}
        ~Iterator() = default;

        ValueType& operator*();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator+=(size_t value);
        bool operator!=(const Iterator& other);
        bool operator==(const Iterator& other);

    private:
        Node* _ptr;
    };
    Iterator begin();
    Iterator end();

public:
    SLL();

    SLL(const SLL& other);
    SLL& operator=(const SLL& other);
    SLL(SLL&& other) noexcept;
    SLL& operator=(SLL&& other) noexcept;
    ~SLL();

    void pushFront(ValueType value);
    void insert(size_t idx, ValueType value);

    void popFront();
    void erase(size_t idx);
    void clear();

    ValueType& front() const;
    size_t size() const noexcept;
    ValueType& operator[](size_t idx);
    const ValueType& operator[](size_t idx) const;

private:
    Node* _head;
    size_t _size;
};