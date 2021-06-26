#pragma once
#include <cstddef>

enum class ResizeStrategy {
    Additive,
    Multiplicative
};

using ValueType = int;

class MyVector {
public:
    class Iterator {
    public:
        Iterator() = default;
        Iterator(ValueType* ptr);

        ValueType& operator*();

        Iterator& operator++();
        Iterator& operator--();

        Iterator operator++(int);
        Iterator operator--(int);

        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);

    private:
        ValueType* _ptr;
    };
    Iterator begin();
    Iterator end();


public:
    MyVector(ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);
    MyVector(size_t size,
             ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);
    MyVector(size_t size,
             const ValueType& value,
             ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);
    MyVector(size_t size,
             const ValueType* rawVector,
             ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative,
             float coef = 2);

    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    ValueType& at(size_t idx);
    const ValueType& at(size_t idx) const;
    ValueType& operator[](const size_t idx);
    const ValueType& operator[](const size_t idx) const;

    // Если размер вставляемого больше чем capacity +=/*= coef,
    // то capacity = размер вставляемого + size
    void insert(Iterator pos, const ValueType& value);
    void insert(size_t idx, const ValueType& value);
    void pushBack(const ValueType& value);

    // Очистить вектор без изменения capacity
    void clear() noexcept;

    void erase(Iterator pos, size_t len = 1);
    void erase(size_t idx, size_t len = 1);
    void popBack();

    // Задать size
    // Если новый size больше старого - записываем в новые элементы value
    // Если меньше - обрезаем вектор
    void resize(size_t newSize, const ValueType& value = ValueType());

    // Задать capacity
    // Уменьшать capacity нельзя
    void reserve(size_t capacity);

    // Сделать capacity равным size
    void shrinkToFit();


    ValueType& front() const noexcept;
    ValueType& back() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    float loadFactor() const noexcept;

    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть end
    Iterator find(const ValueType& value, bool isBegin = true);

private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _resizeStrategy;
    float _coef;
};