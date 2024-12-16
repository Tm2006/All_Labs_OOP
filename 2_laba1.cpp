#include <iostream>
#include <initializer_list>
#include <stdexcept>

namespace containers {

    template<typename T>
    class Queue {
    public:
        struct Node {

            friend class Queue;

            T value;
        private:
            Node* next;

            Node(const T& val) : value(val), next(nullptr) {}
        };
    private:
        Node* _head;
        Node* _tail;
        size_t _size;
        
    public:
        // Конструктор по умолчанию
        Queue() : _head(nullptr), _tail(nullptr), _size(0) {}

        // Конструктор от std::initializer_list<T>
        Queue(std::initializer_list<T> initList) : Queue() {
            for (const T& item : initList) {
                push_back(item);
            }
        }

        // Конструктор копирования
        Queue(const Queue& other) : Queue() {
            Node* current = other._head;
            while (current) {
                push_back(current->value);
                current = current->next;
            }
        }

        // Копирующий оператор присваивания
        Queue& operator=(const Queue& other) {
            if (this != &other) {
                clear();
                Node* current = other._head;
                while (current) {
                    push_back(current->value);
                    current = current->next;
                }
            }    
            return *this;
        }

        // Конструктор перемещения
        Queue(Queue&& other) noexcept : _head(other._head), _tail(other._tail), _size(other._size) {
            other._head = nullptr;
            other._tail = nullptr;
            other._size = 0;
        }

        // Перемещающий оператор присваивания
        Queue& operator=(Queue&& other) noexcept {
            if (this != &other) {
                clear();
                _head = other._head;
                _tail = other._tail;
                _size = other._size;
                other._head = nullptr;
                other._tail = nullptr;
                other._size = 0;
            }
            return *this;
        }

        // Деструктор
        ~Queue() {
            clear();
        }

        // Метод добавления элемента в конец
        void push_back(const T& value) {
            Node* newNode = new Node(value);
            if (_tail == nullptr) {
                _head = _tail = newNode;
            }
            else {
                _tail->next = newNode;
                _tail = newNode;
            }
            ++_size;
        }


        // Метод удаления элемента из начала
        void pop_front() {
            if (!_head) {
                throw std::out_of_range("Queue is empty");
            }
            Node* temp = _head;
            _head = _head->next;
            delete temp;
            if (!_head) {
                _tail = nullptr;
            }
            --_size;
        }

        // Метод получения элемента по индексу
        T& operator[](size_t index) {
            if (index >= _size) {
                throw std::out_of_range("Index out of range");
            }
            Node* current = _head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        // Метод очистки очереди
        void clear() {
            while (_head) {
                pop_front();
            }
        }

        // Метод получения размера очереди
        size_t size() const {
            return _size;
        }
    };

} // namespace containers

int main() {

    containers::Queue<int> intQueue = { 1, 2, 3, 4, 5 };
    containers::Queue<double> doubleQueue = { 1.1, 2.2, 3.3 };
    containers::Queue<std::string> stringQueue = { "one", "two", "three" };

    // Демонстрация работы с очередью int
    std::cout << "Int Queue: ";
    for (size_t i = 0; i < intQueue.size(); ++i) {
        std::cout << intQueue[i] << " ";
    }
    std::cout << std::endl;

    // Демонстрация работы с очередью double
    std::cout << "Double Queue: ";
    for (size_t i = 0; i < doubleQueue.size(); ++i) {
        std::cout << doubleQueue[i] << " ";
    }
    std::cout << std::endl;

    // Демонстрация работы с очередью string
    std::cout << "String Queue: ";
    for (size_t i = 0; i < stringQueue.size(); ++i) {
        std::cout << stringQueue[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

