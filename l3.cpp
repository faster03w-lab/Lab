#include <iostream>
using namespace std;

int main() {
    //ПУНКТ 1
    setlocale(LC_ALL, "RU");
    int N;
    cout << "Введите N: ";
    cin >> N;

    if (N <= 0) {
        cout << "Последовательность пуста." << endl;
        return 0;
    }

    int sum = 0;
    int max = -1000000000; // очень маленькое число
    int pos = 0;
    int found = 0; // 0 = не найдено, 1 = найдено

    cout << "Введите " << N << " чисел:" << endl;

    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;

        // Получаем последнюю цифру (всегда положительную)
        int last = a % 10;
        if (last < 0) {
            last = -last;
        }

        // Пропускаем, если не оканчивается на 2
        if (last != 2) {
            continue;
        }

        // Если дошли сюда — число подходит
        sum = sum + a;
        found = 1;

        // Обновляем максимум и позицию
        if (a > max) {
            max = a;
            pos = i;
        }
    }

    if (found == 0) {
        cout << "Нет чисел, оканчивающихся на 2." << endl;
    }
    else {
        cout << "Сумма: " << sum << endl;
        cout << "Наибольшее число: " << max << endl;
        cout << "Номер в последовательности: " << pos << endl;
    }

    cout << endl;

    //ПУНКТ 2
    int x;
    cout << "Введите x (|x| < 1000): ";
    cin >> x;

    // Проверка условия |X| < 1000
    if (x >= 1000 || x <= -1000) {
        cout << "Ошибка: |x| должно быть строго меньше 1000!" << endl;
        return 0;
    }

    // Обработка нуля
    if (x == 0) {
        cout << "Зеркальное отражение: 0" << endl;
        return 0;
    }

    // Запоминаем знак с помощью int (0 = положительное, 1 = отрицательное)
    int minus = 0;
    int absx = x;
    if (x< 0) {
        minus = 1;
        absx = -x; // делаем положительным
    }

    // Переворачиваем число
    int rev = 0;
    int temp = absx;

    while (temp != 0) {
        rev = rev * 10 + temp % 10;
        temp = temp / 10;
    }

    // Возвращаем знак, если был
    if (minus == 1) {
        rev = -rev;
    }

    cout << "Зеркальное отражение: " << rev << endl;

    return 0;
}