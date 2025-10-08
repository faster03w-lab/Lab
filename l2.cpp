#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    // === ПУНКТ 1 ===
    short A;
    int i;

    cout << "Введите число A: ";
    cin >> A;

    cout << "Введите номер бита i (0-15): ";
    cin >> i;

    if (i < 0 || i > 15) {
        cout << "Ошибка! Бит от 0 до 15." << endl;
        return 0;
    }

    //i-й бит
    int bit = (A >> i) & 1;
    cout << "Бит " << i << " = " << bit << endl;

    if (bit != 0) {
        // Умножаем на 5
        short res = A * 5;
        cout << "A * 5 = " << res << " = ";

        // Выводим 8 бит(от старшего к младшему)
        cout << ((res >> 7) & 1);
        cout << ((res >> 6) & 1);
        cout << ((res >> 5) & 1);
        cout << ((res >> 4) & 1);
        cout << ((res >> 3) & 1);
        cout << ((res >> 2) & 1);
        cout << ((res >> 1) & 1);
        cout << ((res >> 0) & 1);
        cout << endl;
    }
    else {
        // Инвертируем
        short inv = -A - 1;;
        cout << "~A = " << inv << " = ";

        cout << ((inv >> 7) & 1);
        cout << ((inv >> 6) & 1);
        cout << ((inv >> 5) & 1);
        cout << ((inv >> 4) & 1);
        cout << ((inv >> 3) & 1);
        cout << ((inv >> 2) & 1);
        cout << ((inv >> 1) & 1);
        cout << ((inv >> 0) & 1);
        cout << endl;
    }

    //ПУНКТ 2
    int N;
    cout << "\nВведите чит-код: ";
    cin >> N;

    switch (N) {
    case 101:
    case 102:
    case 103:
        cout << "Чит-код " << N << ": +1000 золота" << endl;
        break;
    case 201:
    case 202:
        cout << "Чит-код " << N << ": полное здоровье и мана" << endl;
        break;
    case 300:
        cout << "Чит-код " << N << ": оружие и броня" << endl;
        break;
    case 999:
        cout << "Чит-код " << N << ": победа!" << endl;
        break;
    default:
        cout << "Код не найден" << endl;
    }
    //ПАМЯТЬ
    cout << "\nПамять:" << endl;
    cout << "Если хранить всё отдельно: 27 байт" << endl;
    cout << "В программе с выравниванием: ~32 байт" << endl;

    return 0;
}