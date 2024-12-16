#include <iostream>
#include <iomanip>  // Для std::hex и std::oct

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    char ch;

    while (true) {
        cout << "Введите символ (или 'q' для выхода): ";
        cin >> ch;

        if (ch == 'q') {
            break;  // Выход из программы, если введен символ 'q'
        }

        cout << "Символ: " << ch
            << ", Шестнадцатеричный код: " << hex << (int)ch
            << ", Восьмеричный код: " << oct << (int)ch
            << endl;

        // Возвращаем формат в десятичный, чтобы следующее число выводилось правильно
        cout << dec;
    }

    return 0;
}
