#include <iostream>
#include <cmath>
using namespace std;

// Функция для одного числа: ближайшее кратное 5
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

// Функция для трёх чисел: сумма минимального и максимального
int sum(int a, int b, int c) {
    cout << "исп. функция суммы максимума и минимума из трёх чисел" << endl;
    int mx = a, mn = a;
    if (b > mx) mx = b;
    if (c > mx) mx = c;
    if (b < mn) mn = b;
    if (c < mn) mn = c;
    return mx + mn;
}

// Пункт 2: void-функция
void f2() {
    cout << "выполнена void-функция " << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Выберите пункт задания (1 или 2): ";
    int d;
    cin >> d;

    if (d == 1) {
        cout << "Введите три целых числа (0 = отсутствует): ";
        int x, y, z;
        cin >> x >> y >> z;

        int count = 0;
        if (x != 0) count++;
        if (y != 0) count++;
        if (z != 0) count++;

        if (x == 0 && y == 0 && z == 0) {
            int result = k5(0);
            cout << "Результат: " << result << endl;
        }
        else if (count == 1) {
            int num = (x != 0) ? x : (y != 0 ? y : z);
            int result = k5(num);
            cout << "Результат: " << result << endl;
        }
        else if (count == 3) {
            int result = sum(x, y, z);
            cout << "Результат: " << result << endl;
        }
        else {
            cout << "Ошибка: поддерживаются только 1 или 3 числа." << endl;
        }
    }

    if (d == 2) {
        f2();
    }

    if (d != 1 && d != 2) {
        cout << "Неверный выбор. Введите 1 или 2." << endl;
    }

    return 0;
}