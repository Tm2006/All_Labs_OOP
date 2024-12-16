#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"

// Пример использования Stack<List<std::string>>
template<typename T>
void demo(std::initializer_list<T> data) {
    Stack<List<T>> stack;
    
    stack.push(List<T>(data));
    stack.push(List<T>(data));

    while (!stack.empty()) {

        auto& top = stack.top();

        while (!top.empty()) {
            std::cout << top.back() << " ";
            top.pop_back();
        }

        std::cout << std::endl;
        stack.pop();
    }

    try {
        stack.top();
    }
    catch (std::out_of_range& err) {
        std::cout << err.what() << std::endl;
    }
}

int main() {

    demo<int>({ 1,2,3,4,5 });
    demo<double>({ 1.1,2.1,3.1,4.1,5.1 });
    demo<std::string>({ "hello", "world", "!" });

    return 0;
}

