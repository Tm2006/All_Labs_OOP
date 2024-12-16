#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Функция для генерации входного файла
void generateInputFile(const string& filename) {
    ofstream infile(filename);
    if (!infile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    // Инициализация генератора случайных чисел
    srand(time(0));

    for (int i = 0; i < 100; ++i) {
        int num = rand() % 101 - 50;  // Генерация числа от -50 до 50
        infile << num << endl;
    }

    infile.close();
}

// Функция для обработки данных и записи в выходной файл
void processFile(const string& inputFilename, const string& outputFilename) {
    ifstream infile(inputFilename);
    ofstream outfile(outputFilename);
    if (!infile) {
        cerr << "Не удалось открыть входной файл." << endl;
        return;
    }
    if (!outfile) {
        cerr << "Не удалось открыть выходной файл." << endl;
        return;
    }

    vector<int> numbers;
    int num;

    // Чтение чисел из входного файла
    while (infile >> num) {
        numbers.push_back(num);
    }

    // Вычисление среднего арифметического всех чисел
    int sum = 0;
    for (int n : numbers) {
        sum += n;
    }
    double average = static_cast<double>(sum) / numbers.size();

    // Запись чисел в выходной файл, деля нечетные по абсолютной величине на среднее арифметическое
    for (int n : numbers) {
        if (n % 2 != 0) {  // Проверка на нечетное число
            outfile << static_cast<double>(n) / average << endl;
        }
        else {
            outfile << n << endl;  // Для четных чисел просто записываем их
        }
    }

    infile.close();
    outfile.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    string inputFilename = "input.txt";
    string outputFilename = "output.txt";

    // Генерация входного файла
    generateInputFile(inputFilename);

    // Обработка файла и запись в выходной файл
    processFile(inputFilename, outputFilename);

    cout << "Обработка завершена. Результат записан в файл " << outputFilename << endl;
    return 0;
}
