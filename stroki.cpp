#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <windows.h>

using namespace std;


const unsigned char vowels[] = {
    0xE0, 0xE5, 0xB8, 0xE8, 0xEE, 0xF3, 0xFA, 0xFB, 0xFC, 0xFD, 0xFF, // аеёиоуъыьэюя
    0xC0, 0xC5, 0xA8, 0xC8, 0xCE, 0xD3, 0xDA, 0xDB, 0xDC, 0xDD, 0xDF  // АЕЁИОУЪЫЬЭЮЯ
};


bool isRussianVowel(char ch) {
    unsigned char uch = (unsigned char)ch;
    for (int i = 0; i < 22; i++) {
        if (uch == vowels[i]) return true;
    }
    return false;
}

// Функция для проверки, является ли символ русской буквой
bool isRussianLetter(char ch) {
    unsigned char uch = (unsigned char)ch;
    // Русские буквы в CP1251: а-я = 0xE0-0xFF, А-Я = 0xC0-0xDF, ё = 0xB8, Ё = 0xA8
    return (uch >= 0xC0 && uch <= 0xDF) || (uch >= 0xE0 && uch <= 0xFF) || uch == 0xB8 || uch == 0xA8;
}

// Функция для преобразования русской буквы в нижний регистр
char toRussianLower(char ch) {
    unsigned char uch = (unsigned char)ch;
    if (uch >= 0xC0 && uch <= 0xDF) { // Заглавные А-Я
        return (char)(uch + 0x20);
    }
    if (uch == 0xA8) return (char)0xB8; // Ё -> ё
    return ch;
}

// Пункт 0: Вывод таблицы символов и их кодов
void printCharTable() {
    cout << "\n=== Таблица символов и их кодов ===\n";
    cout << "Символ\tКод(dec)\tКод(hex)\tСимвол\tКод(dec)\tКод(hex)\n";

    // Русские буквы
    const char* rusLower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    const char* rusUpper = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const char* engLower = "abcdefghijklmnopqrstuvwxyz";
    const char* engUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* digits = "0123456789";
    const char* punctuation = ".,!?;:-()\"' ";

    cout << "\n--- Русские буквы (строчные) ---\n";
    for (int i = 0; i < 33; i++) {
        unsigned char ch = rusLower[i];
        cout << rusLower[i] << "\t" << (int)ch << "\t0x" << hex << (int)ch << dec << "\n";
    }

    cout << "\n--- Русские буквы (заглавные) ---\n";
    for (int i = 0; i < 33; i++) {
        unsigned char ch = rusUpper[i];
        cout << rusUpper[i] << "\t" << (int)ch << "\t0x" << hex << (int)ch << dec << "\n";
    }

    cout << "\n--- Английские буквы ---\n";
    for (int i = 0; i < 26; i++) {
        cout << engLower[i] << "\t" << (int)engLower[i] << "\t\t";
        cout << engUpper[i] << "\t" << (int)engUpper[i] << "\n";
    }

    cout << "\n--- Цифры ---\n";
    for (int i = 0; i < 10; i++) {
        cout << digits[i] << "\t" << (int)digits[i] << "\n";
    }

    cout << "\n--- Знаки препинания ---\n";
    for (int i = 0; punctuation[i] != '\0'; i++) {
        cout << punctuation[i] << "\t" << (int)punctuation[i] << "\n";
    }
    cout << "===============================\n\n";
}


void removeVowels() {
    char str[101];
    char result[101];

    cout << "Введите строку (не более 100 символов): ";
    cin.getline(str, 101);

    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isRussianVowel(str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    cout << "Результат: " << result << endl;
}
bool isLetter(char ch) {
    unsigned char uch = (unsigned char)ch;
    return isalpha(uch) || isRussianLetter(ch);
}


bool isLetterOrDigit(char ch) {
    unsigned char uch = (unsigned char)ch;
    return isalnum(uch) || isRussianLetter(ch);
}


void getCleanWord(char* word, const char* original) {
    int start = 0;
    int end = (int)strlen(original) - 1;

    // Ищем начало слова
    while (start <= end && !isLetterOrDigit(original[start]) && original[start] != '-' && original[start] != '\'') {
        start++;
    }

    // Ищем конец слова
    while (end >= start && !isLetter(original[end]) && !isdigit(original[end])) {
        end--;
    }

    if (start <= end) {
        int len = 0;
        for (int i = start; i <= end; i++) {
            if (isLetter(original[i]) || original[i] == '-') {
                if (isdigit(original[i])) {
                    continue;
                }
                
                if (isRussianLetter(original[i])) {
                    word[len++] = toRussianLower(original[i]);
                }
                else {
                    word[len++] = tolower(original[i]);
                }
            }
        }
        word[len] = '\0';

        
        while (word[0] == '-') {
            for (int i = 0; word[i] != '\0'; i++) {
                word[i] = word[i + 1];
            }
        }
        while (strlen(word) > 0 && word[strlen(word) - 1] == '-') {
            word[strlen(word) - 1] = '\0';
        }
    }
    else {
        word[0] = '\0';
    }
}


bool isAlphabetOrder(const char* word) {
    int len = (int)strlen(word);
    if (len <= 1) return true;

    for (int i = 1; i < len; i++) {
        if ((unsigned char)word[i] < (unsigned char)word[i - 1]) {
            return false;
        }
    }
    return true;
}

bool wordExists(char words[][100], int count, const char* word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return true;
        }
    }
    return false;
}


void findLongestWords() {
    const char* textFilePath = "C:\\Users\\faste\\OneDrive\\Desktop\\text.txt";
    const char* configFilePath = "C:\\Users\\faste\\OneDrive\\Desktop\\input.txt";
    const char* resultFilePath = "C:\\Users\\faste\\OneDrive\\Desktop\\result.txt";

    ifstream inputFile(textFilePath);
    ifstream configFile(configFilePath);
    ofstream resultFile(resultFilePath);

    if (!inputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << textFilePath << endl;
        cout << "Проверьте, существует ли файл по этому пути" << endl;
        return;
    }

    if (!configFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << configFilePath << endl;
        cout << "Создайте файл input.txt на рабочем столе" << endl;
        return;
    }

    int N;
    configFile >> N;
    configFile.close();

    cout << "Прочитано N = " << N << " из файла input.txt" << endl;

    if (N <= 0) {
        cout << "N должно быть положительным числом" << endl;
        return;
    }

    char words[1000][100];
    int lengths[1000];
    int wordCount = 0;

    char buffer[1000];
    char tempWord[100];

    while (inputFile >> buffer) {
        getCleanWord(tempWord, buffer);
        if (strlen(tempWord) > 0) {
            if (isAlphabetOrder(tempWord)) {
                if (!wordExists(words, wordCount, tempWord)) {
                    strcpy(words[wordCount], tempWord);
                    lengths[wordCount] = (int)strlen(tempWord);
                    wordCount++;
                }
            }
        }
    }
    inputFile.close();

    if (wordCount == 0) {
        resultFile << "Нет слов, удовлетворяющих условию" << endl;
        cout << "Нет слов, удовлетворяющих условию" << endl;
        return;
    }

    // Сортировка по убыванию длины
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = 0; j < wordCount - i - 1; j++) {
            if (lengths[j] < lengths[j + 1]) {
                int tempLen = lengths[j];
                lengths[j] = lengths[j + 1];
                lengths[j + 1] = tempLen;

                char tempWord[100];
                strcpy(tempWord, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], tempWord);
            }
        }
    }

    int outputCount = (N < wordCount) ? N : wordCount;
    for (int i = 0; i < outputCount; i++) {
        resultFile << words[i] << " (" << lengths[i] << ")" << endl;
    }

    resultFile.close();

    cout << "\nРезультат сохранен в: " << resultFilePath << endl;
    cout << "Найдено слов: " << wordCount << endl;
    cout << "Записано слов: " << outputCount << endl;
    cout << "\nСамые длинные слова с буквами по алфавиту:\n";
    for (int i = 0; i < outputCount && i < 20; i++) {
        cout << i + 1 << ". " << words[i] << " (длина: " << lengths[i] << ")" << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    printCharTable();

    cout << "\n Задача 1: Удаление гласных букв \n";
    cin.ignore();
    removeVowels();

    cout << "\n Задача 2: Поиск N самых длинных слов \n";
    findLongestWords();

    return 0;
}