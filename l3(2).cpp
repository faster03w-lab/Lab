#include <iostream>
using namespace std;

int main() {
    // Пункт 1
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите количество чисел: ";
    cin >> n;

    if (n <= 0) {
        cout << "Последовательности нет." << endl;
        return 0;
    }

    int sum = 0;
    int max_num = -100000;
    int max_index = -1;
    int found = 0; // 0 = не найдено, 1 = найдено

    cout << "Введите сами числа:" << endl;

    for (int i = 1; i <= n; i++) {
        int num;
        cin >> num;

        // Проверяем последнюю цифру числа
        int last = num % 10;
        if (last < 0) {
            last = -last;
        }

        // Пропускаем числа, не оканчивающиеся на 2
        if (last != 2) {
            continue;
        }

        // Обрабатываем подходящие числа
        if (found == 0) {
            max_num = num;
            max_index = i;
            found = 1;
        }

        sum += num;

        // Обновляем максимум и позицию
        if (num > max_num) {
            max_num = num;
            max_index = i;
        }
    }

    if (found == 0) {
        cout << "Нет чисел, оканчивающихся на 2." << endl;
    }
    else {
        cout << "Сумма: " << sum << endl;
        cout << "Наибольшее число: " << max_num << endl;
        cout << "Номер в последовательности: " << max_index << endl;
    }

    cout << endl;

    // Пункт 2
    int x;
    cout << "Введите  x (|x| < 1000): ";
    cin >> x;

    // Проверка |x| < 1000
    if (x >= 1000 || x <= -1000) {
        cout << "Ошибка: |x| должно быть меньше 1000!" << endl;
        return 0;
    }

    // Если равен 0
    if (x == 0) {
        cout << "Зеркальное отражение: 0" << endl;
        return 0;
    }

    // Сохраняем знак
    int minus = 0;
    if (x < 0) {
        minus = 1;
        x = -x;
    }

    int mirror = 0;
    int copy = x;

    while (copy != 0) {
        mirror = mirror * 10 + copy % 10;
        copy = copy / 10;
    }

    // Возвращаем знак, если был
    if (minus == 1) {
        mirror = -mirror;
    }

    cout << "Зеркальное отражение: " << mirror << endl;

    return 0;
}