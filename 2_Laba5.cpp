#include <iostream>
#include <iomanip>  // ��� std::hex � std::oct

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    char ch;

    while (true) {
        cout << "������� ������ (��� 'q' ��� ������): ";
        cin >> ch;

        if (ch == 'q') {
            break;  // ����� �� ���������, ���� ������ ������ 'q'
        }

        cout << "������: " << ch
            << ", ����������������� ���: " << hex << (int)ch
            << ", ������������ ���: " << oct << (int)ch
            << endl;

        // ���������� ������ � ����������, ����� ��������� ����� ���������� ���������
        cout << dec;
    }

    return 0;
}