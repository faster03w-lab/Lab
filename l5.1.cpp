#include <iostream>
#include <cmath>
#include <climits>
using namespace std;

int k5(int a) {
    cout << "исп. функция ближайшего кратного 5" << endl;
    int r = a % 5;
    if (r < 0) r += 5;
    if (r <= 2) {
        return a - r;
    }
    else {
        return a + (5 - r);
    }
}
int sum(int a, int b, int c) {
    cout << "исп. функция суммы максимума и минимума из трёх чисел" << endl;
    int mx = a, mn = a;
    if (b > mx) mx = b;
    if (c > mx) mx = c;
    if (b < mn) mn = b;
    if (c < mn) mn = c;
    return mx + mn;
}

//П2
void f2(int x) {
    cout << "выполнена void-функция для пункта 2" << endl;

    cout << "Противоположное число: " << -x << endl;
    cout << "Корень 2-й степени: " << sqrt(abs(x)) << endl;


    double root5;
    if (x == 0) {
        root5 = 0.0;
    }
    else if (x > 0) {
        root5 = pow(x, 1.0 / 5.0);
    }
    else {
        root5 = -pow(-x, 1.0 / 5.0);
    }
    cout << "Корень 5-й степени: " << root5 << endl;

    cout << "int: " << sizeof(int) * 8 << " бит, диапазон " << INT_MIN << ", " << INT_MAX << "" << endl;
    cout << "double: " << sizeof(double) * 8 << " бит, диапазон " << -DBL_MAX << ", " << DBL_MAX << "" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Выберите пункт задания (1 или 2): ";
    int d;
    cin >> d;

    if (d == 1) {
        cout << "Введите три целых числа: ";
        int x, y, z;
        cin >> x >> y >> z;

        int n0 = (x != 0) + (y != 0) + (z != 0);

        if (n0 == 0) {
            int res = k5(0);
            cout << "Результат: " << res << endl;
        }
        else if (n0 == 1) {
            int num = x;
            if (y != 0) num = y;
            if (z != 0) num = z;
            int res = k5(num);
            cout << "Результат: " << res << endl;
        }
        else if (n0 == 3) {
            int res = sum(x, y, z);
            cout << "Результат: " << res << endl;
        }
        else {
            cout << "Ошибка: введите 1 или 3 ненулевых числа." << endl;
        }
    }

    else if (d == 2) {
        cout << "Введите целое число x: ";
        int x;
        cin >> x;
        f2(x);
    }

    else {
        cout << "Неверный выбор. Введите 1 или 2." << endl;
    }

    return 0;
}