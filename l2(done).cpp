#include <iostream>
#include <bitset>
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	//П1 

	short A;
	int i;

	cout << "Введите число A: ";
	cin >> A;

	cout << "Введите номер бита i (0-7): ";
	cin >> i;

	if (i < 0 || i > 7) {
		cout << "Ошибка! Бит от 0 до 7." << endl;
		return 0;
	}

	int bit = (A >> i) & 1;
	cout << "Бит " << i << " = " << bit << endl;

	if (bit != 0) {
		short res = A & 5;
		cout << "A * 5 = " << res << " = " << bitset<8>(res) << endl;

	}
	else {
		short inv = ~A;
		cout << "~A = " << inv << " = " << bitset<8>(inv) << endl;
	}
	int N;
	cout << "\nВведите чит-код:";
	cin >> N;

	//П2
	switch (N) {
	case 101:
	case 102:
	case 103:
		cout << "Чит - код " << N << ": +100000 золота" << endl;
		break;
	case 201:
	case 202:
	case 203:
		cout << "Чит - код " << N << ": полное здоровье и мана" << endl;
		break;
	case 301:
	case 302:
	case 303:
		cout << "Чит - код " << N << ": восстановление оружия и брони" << endl;
		break;
	case 401:
	case 402:
	case 403:
		cout << "Чит - код " << N << ": Победа" << endl;
		break;
	case 999:
		cout << " Чит - код " << N << ": Бессмерите" << endl;
		break;
	default:
		cout << "Код не найден" << endl;
	}
}