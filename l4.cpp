#include <iostream>
#include <climits>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    // ПУНКТ 1
    int a[11];

    cout << "Введите 11 чисел: ";
    for (int i = 0; i < 11; i++) {
        cin >> a[i];
    }

    // Сумма первых трёх
    int s = a[0] + a[1] + a[2];

    // Если сумма > 100 — сортируем 
    if (s > 100) {
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 10; j++) {
                if (a[j] > a[j + 1]) {
                    int t = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = t;
                }
            }
        }
    }

    // Вывод массива
    for (int i = 0; i < 11; i++) {
        cout << a[i] << " ";
    }
    cout << endl << endl;

    // ПУНКТ 2: матрица 3x4
    int m[3][4];

    cout << "Введите 12 чисел для матрицы 3x4: ";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> m[i][j];
        }
    }

    // Найдём столбец с самой большой суммой отрицательных чисел
    int stolb = -1;
    int bsum = INT_MIN;

    for (int j = 0; j < 4; j++) {
        int sum = 0;
        bool otric = false; 
        for (int i = 0; i < 3; i++) {
            if (m[i][j] < 0) {
                sum += m[i][j];
                otric = true;
            }
        }
        if (otric && sum > bsum) {
            bsum = sum;
            stolb = j;
        }
    }

    // Обнуляем найденный столбец
    if (stolb != -1) {
        for (int i = 0; i < 3; i++) {
            m[i][stolb] = 0;
        }
    }

    // Вывод матрицы
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl; //добавили перевод строки после каждой строки
    }

    return 0;
}
// 40 40 30 5 2 100 1 99 8 6 7
// -1 -2 5 -3
// -4 0 -6 -7
// -8 1 -9 -10