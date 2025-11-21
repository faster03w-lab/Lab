#include <iostream>
#include <cstdlib>
using namespace std;

// Функция для поиска индексов строк с нулевыми элементами
int* findZeroRows(int** grid, int rowCount, int colCount, int& foundCount) {
    foundCount = 0;

    // Подсчет строк с нулями
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            if (grid[r][c] == 0) {
                foundCount++;
                break;
            }
        }
    }

    if (foundCount == 0) return nullptr;

    int* zeroRowIndices = (int*)malloc(foundCount * sizeof(int));
    int pos = 0;

    // Запись индексов строк с нулями
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            if (grid[r][c] == 0) {
                zeroRowIndices[pos++] = r;
                break;
            }
        }
    }

    return zeroRowIndices;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создание матрицы 2x2
    int** grid = (int**)malloc(2 * sizeof(int*));
    for (int r = 0; r < 2; r++) {
        grid[r] = (int*)malloc(2 * sizeof(int));
    }

    cout << "Введите элементы матрицы 2x2:\n";
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) {
            cin >> grid[r][c];
        }
    }

    int TopRows, LeftCols;
    do {
        cout << "Введите A (строк сверху): ";
        cin >> TopRows;
    } while (TopRows < 0);

    do {
        cout << "Введите B (столбцов слева): ";
        cin >> LeftCols;
    } while (LeftCols < 0);

    int cfRow, cfCol;
    cout << "Введите C и D: ";
    cin >> cfRow >> cfCol;

    // Расширение матрицы
    int rowCount = 2, colCount = 2;

    // Добавляем строки сверху
    grid = (int**)realloc(grid, (rowCount + TopRows) * sizeof(int*));
    for (int r = rowCount - 1; r >= 0; r--) {
        grid[r + TopRows] = grid[r];
    }
    for (int r = 0; r < TopRows; r++) {
        grid[r] = (int*)malloc(colCount * sizeof(int));
    }
    rowCount += TopRows;

    // Добавляем столбцы слева
    for (int r = 0; r < rowCount; r++) {
        grid[r] = (int*)realloc(grid[r], (colCount + LeftCols) * sizeof(int));
        for (int c = colCount - 1; c >= 0; c--) {
            grid[r][c + LeftCols] = grid[r][c];
        }
    }
    colCount += LeftCols;

    // Заполняем матрицу по формуле r*coefRow + c*coefCol
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            grid[r][c] = r * cfRow + c * cfCol;
        }
    }

    cout << "\nМатрица после расширения:\n";
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            cout << grid[r][c] << "\t";
        }
        cout << endl;
    }

    // поиск строк с нулями
    int zeroRowCount;
    int* zeroRowIndices = findZeroRows(grid, rowCount, colCount, zeroRowCount);

    // удаление строк с нулями 
    if (zeroRowCount > 0) {
        // сдвигаем строки вверх, перезаписывая строки с нулями
        int writeRowIndex = 0;
        for (int r = 0; r < rowCount; r++) {
            bool isZeroRow = false;
            for (int c = 0; c < zeroRowCount; c++) {
                if (r == zeroRowIndices[c]) {
                    isZeroRow = true;
                    break;
                }
            }

            if (!isZeroRow) {
                // копируем строку на новую позицию
                if (writeRowIndex != r) {
                    for (int c = 0; c < colCount; c++) {
                        grid[writeRowIndex][c] = grid[r][c];
                    }
                }
                writeRowIndex++;
            }
        }

        // освобождаем память удаленных строк 
        for (int r = rowCount - zeroRowCount; r < rowCount; r++) {
            free(grid[r]);
        }

        // изменяем размер массива указателей
        rowCount -= zeroRowCount;
        grid = (int**)realloc(grid, rowCount * sizeof(int*));

        free(zeroRowIndices);

        cout << "\nМатрица после удаления строк с нулями:\n";
        for (int r = 0; r < rowCount; r++) {
            for (int c = 0; c < colCount; c++) {
                cout << grid[r][c] << "\t";
            }
            cout << endl;
        }
    }
    else {
        cout << "\nСтрок с нулевыми элементами не найдено\n";
    }

    // освобождение памяти
    for (int r = 0; r < rowCount; r++) {
        free(grid[r]);
    }
    free(grid);

    //П2
    int first, second;
    cin >> first >> second;
    cout << first << " " << second << endl;

    // Создаём указатели и выделяем память
    int* num1 = new int(first);
    int* num2 = new int(second);

    // Увеличиваем первое число в два раза
    *num1 = *num1 * 2;

    // Меняем значения местами
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;

    // Сохраняем результат обратно в переменные
    first = *num1;
    second = *num2;

    // Освобождаем память
    delete num1;
    delete num2;

    cout << first << " " << second << endl;