#include <iostream>
#include <cmath>
using namespace std;

//для одного числа: ближайшее кратное 5
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

//для трёх чисел: сумма минимального и максимального
int sum(int a, int b, int c) {
    cout << "исп. функция суммы максимума и минимума из трёх чисел" << endl;
    int mx = a, mn = a;
    if (b > mx) mx = b;
    if (c > mx) mx = c;
    if (b < mn) mn = b;
    if (c < mn) mn = c;
    return mx + mn;
}

// П2: void-функция
void f2() {
    cout << "выполнена void-функция " << endl;
    setlocale(LC_ALL, "Russian");
    int x;
    std::cout << "Введите целое число x: ";
    std::cin >> x;

    // Противоположное число
    int opposite = -x;

    // Корень 2-й степени (всегда неотрицательный)
    double k2 = std::sqrt(std::abs(x));

    // Корень 5-й степени (может быть отрицательным, если x < 0)
    double k5 = (x / std::abs(x)) * std::pow(std::abs(x), 1.0 / 5.0);

    // Вывод информации о типе int
    int k = sizeof(int) * 8;
    int m = INT_MIN;
    int m1 = INT_MAX;

    std::cout << "int, занимает " << k << " бит(а), мин. значение = " << m
        << ", макс. значение = " << m1 << std::endl;

    std::cout << "Противоположное число: " << opposite << std::endl;
    std::cout << "Корень 2-й степени: " << k2 << std::endl;
    std::cout << "Корень 5-й степени: " << k5 << std::endl;

    int k_double = sizeof(double) * 8;
    double min_double = -DBL_MAX;
    double max_double = DBL_MAX;

    std::cout << "double, занимает " << k_double << " бит(а), "
        << "мин. значение = " << -DBL_MAX << ", "
        << "макс. значение = " << DBL_MAX << std::endl;
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

        int count = 0;
        if (x != 0) count++;
        if (y != 0) count++;
        if (z != 0) count++;

        if (x == 0 && y == 0 && z == 0) {
            int result = k5(0);
            cout << "Результат: " << result << endl;
        }
         if (count == 1) {
            int num = (x != 0) ? x : (y != 0 ? y : z);
            int result = k5(num);
            cout << "Результат: " << result << endl;
        }
        if (count == 3) {
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