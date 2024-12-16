#pragma once

#include "list.h"

//  ласс стека на основе двунаправленного списка
template <typename T>
class Stack {
private:
    List<T> _list;

public:
    Stack() : _list() {}

    Stack(std::initializer_list<T> initList) : _list(initList) {}

    Stack(const Stack& other) : _list(other._list) {}

    Stack(Stack&& other) : _list(std::move(other._list)) {}

    Stack& operator=(const Stack& other) {
        _list = other._list;
        return *this;
    }

    Stack& operator=(Stack&& other) {
        _list = std::move(other._list);
        return *this;
    }

    void push(const T& value) {
        _list.push_back(value);
    }

    void pop() {
        if (_list.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        _list.pop_back();
    }

    T& top() const {
        if (_list.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return _list.back();
    }

    bool empty() const {
        return _list.empty();
    }

    size_t size() const {
        return _list.size();
    }

    void swap(Stack& other) {
        _list.swap(other._list);
    }
};
