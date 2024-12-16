#pragma once

template <typename T>
class ShPtr {
private:
    T* ptr;               // Сырой указатель
    int* ref_count;       // Счетчик ссылок

public:
    // Конструктор по умолчанию
    ShPtr() : ptr(nullptr), ref_count(nullptr) {}

    // Конструктор с указателем
    explicit ShPtr(T* p) : ShPtr() {
        if (p) {
            ptr = p;
            ref_count = new int(1)
        }
    }

    // Конструктор копирования
    ShPtr(const ShPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    ShPtr(ShPtr&& other) : ShPtr() {
        other.swap(*this);
    }

    // Оператор присваивания копированием
    ShPtr& operator=(const ShPtr& other) {
        ShPtr(other).swap(*this);
        return *this;
    }

    ShPtr& operator=(ShPtr&& other) {
        ShPtr(std::move(other)).swap(*this);
        return *this;
    }

    // Деструктор
    ~ShPtr() {
        release();
    }

    // Освобождение памяти, если указатель больше никуда не используется
    void release() {
        if (ref_count) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
            }
        }
        ptr = nullptr;
        ref_count = nullptr;
    }

    // Обмен указателями
    void swap(ShPtr& other) {
        std::swap(ptr, other.ptr);
        std::swap(ref_count, other.ref_count);
    }

    // Возвращение сырого указателя
    T* get() const {
        return ptr;
    }

    // Доступ к содержимому по указателю
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // Получение текущего значения счетчика ссылок
    int use_count() const {
        return ref_count ? *ref_count : 0;
    }
};