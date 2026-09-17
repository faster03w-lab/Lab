#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <windows.h>

using namespace std;

// ----- ANSI-цвета -----
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[93m";

// ----- Проверки -----

bool isRussian(unsigned char c) {
    if (c >= 0xC0 && c <= 0xFF) return true;
    if (c == 0xA8 || c == 0xB8) return true;   // Ё и ё
    return false;
}

bool isVowel(unsigned char c) {
    if (c >= 0xC0 && c <= 0xDF) c += 0x20;
    if (c == 0xE0) return true;  // а
    if (c == 0xE5) return true;  // е
    if (c == 0xB8) return true;  // ё
    if (c == 0xE8) return true;  // и
    if (c == 0xEE) return true;  // о
    if (c == 0xF3) return true;  // у
    if (c == 0xFB) return true;  // ы
    if (c == 0xFD) return true;  // э
    if (c == 0xFE) return true;  // ю
    if (c == 0xFF) return true;  // я
    return false;
}

bool isConsonant(unsigned char c) {
    return isRussian(c) && !isVowel(c);
}

bool isDigit(unsigned char c) {
    return c >= '0' && c <= '9';
}

bool isLatin(unsigned char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void addChar(char*& row, int& len, char c) {
    char* newRow = (char*)realloc(row, len + 1);
    if (newRow == NULL) {
        cout << "Ошибка памяти!\n";
        exit(1);
    }
    row = newRow;
    row[len] = c;
    len++;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    string input;
    cout << "Введите строку: ";
    getline(cin, input);
    if (input.size() > 50) input = input.substr(0, 50);

    char** mas = (char**)malloc(4 * sizeof(char*));
    if (mas == NULL) { cout << "Ошибка памяти!\n"; return 1; }
    for (int i = 0; i < 4; i++) mas[i] = NULL;
    int len[4] = { 0, 0, 0, 0 };


    bool inInput[256] = { false };

    for (int i = 0; i < input.size(); i++) {
        unsigned char c = (unsigned char)input[i];
        if (c == '@') continue;
        if (isLatin(c)) continue;

        inInput[c] = true;

        if (isVowel(c))          addChar(mas[0], len[0], c);
        else if (isConsonant(c)) addChar(mas[1], len[1], c);
        else if (isDigit(c))     addChar(mas[2], len[2], c);
        else                     addChar(mas[3], len[3], c);
    }


    cout << "\nМассив:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < len[i]; j++) cout << mas[i][j] << " ";
        cout << "\n";
    }


    string result = input + "+123АБВ";

    cout << "\nРезультат:\n";
    for (int i = 0; i < result.size(); i++) {
        unsigned char c = (unsigned char)result[i];

        if (c == '@') { cout << result[i]; continue; }
        if (isLatin(c)) { cout << result[i]; continue; }

        // Символа не было во вводе → белый
        if (!inInput[c]) {
            cout << result[i];
            continue;
        }

        // Символ был во вводе → красим по категории
        if (isVowel(c))          cout << RED << result[i] << RESET;
        else if (isConsonant(c)) cout << BLUE << result[i] << RESET;
        else if (isDigit(c))     cout << GREEN << result[i] << RESET;
        else                     cout << YELLOW << result[i] << RESET;
    }
    cout << endl;

    for (int i = 0; i < 4; i++) free(mas[i]);
    free(mas);
    return 0;
}