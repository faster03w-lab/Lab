#include <iostream>
#include <cstdlib>
using namespace std;

// Функция для поиска индексов строк, содержащих хотя бы один нулевой элемент
int* locateRowsWithZeros(int** grid, int height, int width, int& totalFound) {
    totalFound = 0;

    // Подсчитываем количество строк с нулями
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            if (grid[r][c] == 0) {
                ++totalFound;
                break;
            }
        }
    }

    if (totalFound == 0) return nullptr;

    int* indices = (int*)malloc(totalFound * sizeof(int));
    int pos = 0;

    // Сохраняем индексы строк с нулями
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            if (grid[r][c] == 0) {
                indices[pos++] = r;
                break;
            }
        }
    }

    return indices;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаём исходную матрицу 2×2
    int** data = (int**)malloc(2 * sizeof(int*));
    for (int r = 0; r < 2; ++r) {
        data[r] = (int*)malloc(2 * sizeof(int));
    }

    cout << "Введите элементы матрицы 2x2:\n";
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            cin >> data[r][c];
        }
    }

    // Ввод параметров A и B с проверкой
    int topRows, leftCols;
    do {
        cout << "Введите A (количество строк сверху): ";
        cin >> topRows;
    } while (topRows < 0);

    do {
        cout << "Введите B (количество столбцов слева): ";
        cin >> leftCols;
    } while (leftCols < 0);

    int coeffC, coeffD;
    cout << "Введите C и D: ";
    cin >> coeffC >> coeffD;

    int currentRows = 2, currentCols = 2;

    // Добавляем строки сверху
    data = (int**)realloc(data, (currentRows + topRows) * sizeof(int*));
    for (int r = currentRows - 1; r >= 0; --r) {
        data[r + topRows] = data[r];
    }
    for (int r = 0; r < topRows; ++r) {
        data[r] = (int*)malloc(currentCols * sizeof(int));
    }
    currentRows += topRows;

    // Добавляем столбцы слева
    for (int r = 0; r < currentRows; ++r) {
        data[r] = (int*)realloc(data[r], (currentCols + leftCols) * sizeof(int));
        for (int c = currentCols - 1; c >= 0; --c) {
            data[r][c + leftCols] = data[r][c];
        }
    }
    currentCols += leftCols;

    // Заполняем новую матрицу по формуле: элемент[r][c] = r * C + c * D
    for (int r = 0; r < currentRows; ++r) {
        for (int c = 0; c < currentCols; ++c) {
            data[r][c] = r * coeffC + c * coeffD;
        }
    }

    cout << "\nМатрица после расширения:\n";
    for (int r = 0; r < currentRows; ++r) {
        for (int c = 0; c < currentCols; ++c) {
            cout << data[r][c] << "\t";
        }
        cout << endl;
    }

    // Поиск строк с нулями
    int foundCount;
    int* zeroIndices = locateRowsWithZeros(data, currentRows, currentCols, foundCount);

    // Удаление строк, содержащих нули
    if (foundCount > 0) {
        int newRow = 0;
        for (int r = 0; r < currentRows; ++r) {
            bool shouldBeRemoved = false;
            for (int i = 0; i < foundCount; ++i) {
                if (r == zeroIndices[i]) {
                    shouldBeRemoved = true;
                    break;
                }
            }

            if (!shouldBeRemoved) {
                if (newRow != r) {
                    for (int c = 0; c < currentCols; ++c) {
                        data[newRow][c] = data[r][c];
                    }
                }
                ++newRow;
            }
        }

        // Освобождаем память удаляемых строк
        for (int r = currentRows - foundCount; r < currentRows; ++r) {
            free(data[r]);
        }

        // Обновляем размер массива строк
        currentRows -= foundCount;
        data = (int**)realloc(data, currentRows * sizeof(int*));

        free(zeroIndices);

        cout << "\nМатрица после удаления строк с нулями:\n";
        for (int r = 0; r < currentRows; ++r) {
            for (int c = 0; c < currentCols; ++c) {
                cout << data[r][c] << "\t";
            }
            cout << endl;
        }
    }
    else {
        cout << "\nСтрок с нулевыми элементами не найдено.\n";
    }

    // Освобождение всей выделенной памяти
    for (int r = 0; r < currentRows; ++r) {
        free(data[r]);
    }
    free(data);

    // Работа с указателями
    int valX, valY;
    cout << "\nВведите два числа a и b: ";
    cin >> valX >> valY;

    int* ptrX = &valX;
    int* ptrY = &valY;

    *ptrX *= 2; // Удваиваем a

    int swapTemp = *ptrX;
    *ptrX = *ptrY;
    *ptrY = swapTemp;

    cout << "После операций:\n";
    cout << "a = " << valX << ", b = " << valY << endl;

    return 0;
}
