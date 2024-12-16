#pragma once

template <typename T>
class ShPtr {
private:
    T* ptr;               // ����� ���������
    int* ref_count;       // ������� ������

public:
    // ����������� �� ���������
    ShPtr() : ptr(nullptr), ref_count(nullptr) {}

    // ����������� � ����������
    explicit ShPtr(T* p) : ShPtr() {
        if (p) {
            ptr = p;
            ref_count = new int(1)
        }
    }

    // ����������� �����������
    ShPtr(const ShPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    ShPtr(ShPtr&& other) : ShPtr() {
        other.swap(*this);
    }

    // �������� ������������ ������������
    ShPtr& operator=(const ShPtr& other) {
        ShPtr(other).swap(*this);
        return *this;
    }

    ShPtr& operator=(ShPtr&& other) {
        ShPtr(std::move(other)).swap(*this);
        return *this;
    }

    // ����������
    ~ShPtr() {
        release();
    }

    // ������������ ������, ���� ��������� ������ ������ �� ������������
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

    // ����� �����������
    void swap(ShPtr& other) {
        std::swap(ptr, other.ptr);
        std::swap(ref_count, other.ref_count);
    }

    // ����������� ������ ���������
    T* get() const {
        return ptr;
    }

    // ������ � ����������� �� ���������
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // ��������� �������� �������� �������� ������
    int use_count() const {
        return ref_count ? *ref_count : 0;
    }
};