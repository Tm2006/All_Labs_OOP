#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>

using namespace std;

// Класс исключений
class CustomException : public exception {
private:
    string message;
    double value;
    int errorCode;

public:
    CustomException(const string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    double getValue() const {
        return value;
    }

    int getErrorCode() const {
        return errorCode;
    }
};

class Num 
{
public:
    double Value;

    Num(double value): Value(value)
    {
    }

    static friend Num operator*(Num a, Num b)
    {
        return a.Value * b.Value;
    }

    static friend Num operator+(Num a, Num b)
    {
        return a.Value + b.Value;
    }

    static friend Num operator-(Num a, Num b)
    {
        return a.Value - b.Value;
    }

    static friend Num operator/(Num a, Num b)
    {
        if (b.Value == 0.0) {
            throw CustomException("division by zero", a.Value, 42);
        }

        return a.Value / b.Value;
    }
};

Num calcZ1(const Num& a) {
    return 1.0 / ((1.0 + a + a * a) / (2.0 * a + a * a) + 2.0 - (1.0 - a + a * a) / (2.0 * a - a * a)) * (5.0 - 2.0 * a * a);
}

Num calcZ2(const Num& x) {
    return (4 - x * x) / 2.0;
}

int main()
{
    cin.exceptions(istream::failbit | istream::badbit);

    try {
        double a, x;

        cout << "Enter value for a: ";
        cin >> a;

        double Z1 = calcZ1(a).Value;
        double Z2 = calcZ2(a).Value;

        cout << "Z1 = " << Z1 << endl;
        cout << "Z2 = " << Z2 << endl;

        if (abs(Z1 - Z2) < 1e-6) {
            cout << "Z1 and Z2 are approximately equal." << endl;
        }
        else {
            cout << "Z1 and Z2 are not equal." << endl;
        }
    }
    catch (const CustomException& e) {
        cerr << "An error occurred: " << e.what() << endl;
        cerr << "Value causing error: " << e.getValue() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
    catch (const exception& e) {
        cerr << "Standard exception: " << e.what() << endl;
    }
}
