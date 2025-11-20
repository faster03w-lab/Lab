#include <iostream>
#include <cstdlib>

using namespace std;

// функция находит строки, содержащие хотя бы один ноль
// Возвращает одномерный массив индексов таких строк
// count — количество найденных строк
int* findRowsWithZero(int** matrix, int rows, int cols, int* count) {
    int* temp = (int*)malloc(rows * sizeof(int)); // максимум rows строк могут содержать 0
    *count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                temp[(*count)++] = i;
                break; // переходим к следующей строке — достаточно одного нуля
            }
        }
    }

    return temp;
}

int main() {
    setlocale(LC_ALL, "Russian");

    //создаем матрицу 2x2
    int** initialMatrix = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        initialMatrix[i] = (int*)malloc(2 * sizeof(int));
    }

    cout << "Введите элементы матрицы 2x2:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            cin >> initialMatrix[i][j];
        }
    }


    int A = initialMatrix[0][0];
    int B = initialMatrix[0][1];
    int C = initialMatrix[1][0];
    int D = initialMatrix[1][1];

    // проверка A и B < 0 
    while (A < 0 || B < 0) {
        cout << "Ошибка: A и B не могут быть отрицательными. Введите новые значения:" << endl;
        cout << "A: ";
        cin >> A;
        cout << "B: ";
        cin >> B;

        // Обновить значения в начальной матрице
        initialMatrix[0][0] = A;
        initialMatrix[0][1] = B;
    }

    // освобождить память начальной матрицы
    for (int i = 0; i < 2; i++) {
        free(initialMatrix[i]);
    }
    free(initialMatrix);

    // расширенная матрица
    int rows = 2 + A;   // добавляем A строк сверху
    int cols = 2 + B;   // добавляем B столбцов слева

    int** matrix = (int**)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)calloc(cols, sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * C + j * D;
        }
    }

    cout << "\nРасширенная матрица:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    //найти строки, содержащие хотя бы один ноль
    int deleteCount = 0;
    int* rowsToDelete = findRowsWithZero(matrix, rows, cols, &deleteCount);

    cout << "\nСтроки, содержащие ноль: ";
    if (deleteCount == 0) {
        cout << "Нет";
    }
    else {
        for (int i = 0; i < deleteCount; i++) {
            cout << rowsToDelete[i] << " ";
        }
    }
    cout << endl;

   
    cout << "\nМатрица после удаления строк, содержащих ноль:" << endl;

    bool hasRemaining = false;
    for (int i = 0; i < rows; i++) {
        bool containsZero = false;
        for (int k = 0; k < deleteCount; k++) {
            if (rowsToDelete[k] == i) {
                containsZero = true;
                break;
            }
        }
        if (!containsZero) {
            hasRemaining = true;
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    if (!hasRemaining) {
        cout << "Все строки были удалены (матрица пуста)." << endl;
    }
 

    // Освобождение памяти
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(rowsToDelete);

    return 0;
}