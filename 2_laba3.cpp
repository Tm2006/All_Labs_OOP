#include <iostream>
#include <string>
#include <vector>

template <typename T>
class ShPtr {
private:
    T* ptr;               // ����� ���������
    int* ref_count;       // ������� ������

    // ������������ ������, ���� ��������� ������ ������ �� ������������
    void release() {
        if (ref_count) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
                ptr = nullptr;
                ref_count = nullptr;
            }
        }
    }

public:
    // ����������� �� ���������
    ShPtr() : ptr(nullptr), ref_count(new int(0)) {}

    // ����������� � ����������
    explicit ShPtr(T* p) : ptr(p), ref_count(new int(1)) {}

    // ����������� �����������
    ShPtr(const ShPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    // �������� ������������ ������������
    ShPtr& operator=(const ShPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            if (ref_count) {
                (*ref_count)++;
            }
        }
        return *this;
    }

    // ����������
    ~ShPtr() {
        release();
    }

    // ��������� ���������
    void reset() {
        release();
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
        //if (ref_count != nullptr)
        //    return *ref_count;
        //else
        //    return 0;
        return ref_count ? *ref_count : 0;
    }

};


int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        std::cout << "����:\n";
        std::cout << "1. ������������ � int\n";
        std::cout << "2. ������������ � double\n";
        std::cout << "3. ������������ �� string\n";
        std::cout << "0. �����\n";
        std::cout << "�������� �����: ";
        std::cin >> choice;

        if (choice == 1) {
            ShPtr<int> p1(new int(10));
            std::cout << "�������� p1: " << *p1 << ", ������� ������: " << p1.use_count() << '\n';

            ShPtr<int> p2 = p1;
            std::cout << "�������� p2: " << *p2 << ", ������� ������: " << p2.use_count() << '\n';

            p1.reset();
            std::cout << "����� ��������� p1, ������� ������ p2: " << p2.use_count() << '\n';
        }
        else if (choice == 2) {
            ShPtr<double> p1(new double(20.5));
            std::cout << "�������� p1: " << *p1 << ", ������� ������: " << p1.use_count() << '\n';

            ShPtr<double> p2 = p1;
            std::cout << "�������� p2: " << *p2 << ", ������� ������: " << p2.use_count() << '\n';

            p1.reset();
            std::cout << "����� ��������� p1, ������� ������ p2: " << p2.use_count() << '\n';
        }
        else if (choice == 3) {
            ShPtr<std::string> p1(new std::string("Hello, world!"));
            std::cout << "�������� p1: " << *p1 << ", ������� ������: " << p1.use_count() << '\n';

            ShPtr<std::string> p2 = p1;
            std::cout << "�������� p2: " << *p2 << ", ������� ������: " << p2.use_count() << '\n';

            p1.reset();
            std::cout << "����� ��������� p1, ������� ������ p2: " << p2.use_count() << '\n';
        }
    } while (choice != 0);

    return 0;
}
