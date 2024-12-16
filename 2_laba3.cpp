#include <iostream>
#include <string>
#include <vector>

template <typename T>
class ShPtr {
private:
    T* ptr;               // Сырой указатель
    int* ref_count;       // Счетчик ссылок

    // Освобождение памяти, если указатель больше никуда не используется
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
    // Конструктор по умолчанию
    ShPtr() : ptr(nullptr), ref_count(new int(0)) {}

    // Конструктор с указателем
    explicit ShPtr(T* p) : ptr(p), ref_count(new int(1)) {}

    // Конструктор копирования
    ShPtr(const ShPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    // Оператор присваивания копированием
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

    // Деструктор
    ~ShPtr() {
        release();
    }

    // Обнуление указателя
    void reset() {
        release();
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
        std::cout << "Меню:\n";
        std::cout << "1. Демонстрация с int\n";
        std::cout << "2. Демонстрация с double\n";
        std::cout << "3. Демонстрация со string\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        if (choice == 1) {
            ShPtr<int> p1(new int(10));
            std::cout << "Значение p1: " << *p1 << ", Счетчик ссылок: " << p1.use_count() << '\n';

            ShPtr<int> p2 = p1;
            std::cout << "Значение p2: " << *p2 << ", Счетчик ссылок: " << p2.use_count() << '\n';

            p1.reset();
            std::cout << "После обнуления p1, Счетчик ссылок p2: " << p2.use_count() << '\n';
        }
        else if (choice == 2) {
            ShPtr<double> p1(new double(20.5));
            std::cout << "Значение p1: " << *p1 << ", Счетчик ссылок: " << p1.use_count() << '\n';

            ShPtr<double> p2 = p1;
            std::cout << "Значение p2: " << *p2 << ", Счетчик ссылок: " << p2.use_count() << '\n';

            p1.reset();
            std::cout << "После обнуления p1, Счетчик ссылок p2: " << p2.use_count() << '\n';
        }
        else if (choice == 3) {
            ShPtr<std::string> p1(new std::string("Hello, world!"));
            std::cout << "Значение p1: " << *p1 << ", Счетчик ссылок: " << p1.use_count() << '\n';

            ShPtr<std::string> p2 = p1;
            std::cout << "Значение p2: " << *p2 << ", Счетчик ссылок: " << p2.use_count() << '\n';

            p1.reset();
            std::cout << "После обнуления p1, Счетчик ссылок p2: " << p2.use_count() << '\n';
        }
    } while (choice != 0);

    return 0;
}
