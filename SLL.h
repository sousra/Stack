#pragma once
#include <iostream>
#include <exception>

template<class T>
class SLL {
    class Node {
    public:
        Node(T value) {
            _next = nullptr;
            _value = value;
        }
        Node* _next;
        T _value;
    };
    Node* getNode(size_t idx);

public:
    class Iterator {
    public:
        Iterator(Node* ptr = nullptr) : _ptr(ptr) {}
        ~Iterator() = default;

        T& operator*();
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

    SLL(const SLL<T>& other);
    SLL(SLL<T>&& other) noexcept;
    SLL& operator=(const SLL<T>& other);
    SLL& operator=(SLL<T>&& other) noexcept;
    ~SLL();

    void pushFront(T value);
    void insert(size_t idx, T value);

    void popFront();
    void erase(size_t idx);
    void clear();

    T& front() const;
    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

    size_t size() const noexcept;

private:
    Node* _head;
    size_t _size;
};

template<class T>
typename SLL<T>::Node* SLL<T>::getNode(size_t idx) {
    if (idx < 0 || idx >= _size) {
        throw std::out_of_range("Invalid index");
    }
    Node* cur = _head;
    size_t i = 0;
    while(i != idx) {
        cur = cur->_next;
        ++i;
    }
    return cur;
}

template<class T>
SLL<T>::SLL() {
    _head = nullptr;
    _size = 0;
}

template<class T>
SLL<T>::SLL(const SLL<T>& other) {
    Node* curNode = other._head;
    while(curNode) {
        insert(_size, curNode->_value);
        curNode = curNode->_next;
    }
}

template<class T>
SLL<T>::SLL(SLL<T>&& other) noexcept {
    _head = other._head;
    _size = other._size;
    other._head = nullptr;
    other._size = 0;
}

template<class T>
SLL<T>& SLL<T>::operator=(const SLL<T>& other) {
    clear();
    Node* curNode = other._head;
    while(curNode) {
        insert(_size, curNode->_value);
        curNode = curNode->_next;
    }
    return *this;
}

template<class T>
SLL<T>& SLL<T>::operator=(SLL<T>&& other) noexcept {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
    return *this;
}

template<class T>
SLL<T>::~SLL() {
    clear();
}

template<class T>
void SLL<T>::pushFront(T value) {
    Node* temp = new Node(value);
    temp->_next = _head;
    _head = temp;
    ++_size;
}

template<class T>
void SLL<T>::insert(size_t idx, T value) {
    if (idx == 0) {
        pushFront(value);
    }
    else if (idx > 0 && idx <= _size) {
        Node* cur = new Node(value);
        Node* prev = getNode(idx - 1);
        cur->_next = prev->_next;
        prev->_next = cur;
        ++_size;
    }
    else {
        throw std::out_of_range("Invalid index");
    }
}

template<class T>
void SLL<T>::popFront() {
    if (_head) {
        Node* temp = _head;
        _head = _head->_next;
        delete temp;
        --_size;
    }
    else {
        throw std::logic_error("Empty linked list");
    }
}

template<class T>
void SLL<T>::erase(size_t idx) {
    if (idx == 0) {
        popFront();
    }
    else if (0 < idx && idx < _size) {
        Node* prev = getNode(idx - 1);
        Node* temp = prev->_next;
        prev->_next = prev->_next->_next;
        delete temp;
        --_size;
    }
    else {
        throw std::out_of_range("Invalid index");
    }
}

template<class T>
void SLL<T>::clear() {
    while(_size != 0) {
        popFront();
    }
}

template<class T>
T& SLL<T>::front() const {
    if (!_head) {
        throw std::logic_error("Empty linked list");
    }
    return _head->_value;
}

template<class T>
T& SLL<T>::operator[](size_t idx) {
    Node* cur = getNode(idx);
    return cur->_value;
}

template<class T>
const T& SLL<T>::operator[](size_t idx) const {
    return operator[](idx);
}

template<class T>
size_t SLL<T>::size() const noexcept {
    return _size;
}

template<class T>
T& SLL<T>::Iterator::operator*() {
    return _ptr->_value;
}

template<class T>
typename SLL<T>::Iterator& SLL<T>::Iterator::operator++() {
    _ptr = _ptr->_next;
    return *this;
}

template<class T>
typename SLL<T>::Iterator SLL<T>::Iterator::operator++(int) {
    SLL::Iterator it(_ptr);
    _ptr = _ptr->_next;
    return it;
}

template<class T>
typename SLL<T>::Iterator& SLL<T>::Iterator::operator+=(size_t value) {
    for (size_t i = 0; i < value; ++i) {
        _ptr = _ptr->_next;
    }
    return *this;
}

template<class T>
bool SLL<T>::Iterator::operator!=(const Iterator& other) {
    return _ptr != other._ptr;
}

template<class T>
bool SLL<T>::Iterator::operator==(const Iterator& other) {
    return _ptr == other._ptr;
}

template<class T>
typename SLL<T>::Iterator SLL<T>::begin() {
    return SLL::Iterator(_head);
}

template<class T>
typename SLL<T>::Iterator SLL<T>::end() {
    return SLL::Iterator(nullptr);
}