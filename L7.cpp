#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>


// Функции для работы с вектором (Пункт 1)
void showVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << " ";
    }
    std::cout << "]\n";
}

// Функция для задания варианта 8
void variantTask(std::vector<int>& vec) {
    std::cout << "До: ";
    showVector(vec);

    if (vec.empty()) {
        std::cout << "Массив пустой!" << std::endl;
        return;
    }

    int minVal = vec[0], maxVal = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < minVal) minVal = vec[i];
        if (vec[i] > maxVal) maxVal = vec[i];
    }

    std::cout << "minVal = " << minVal << ", maxVal = " << maxVal << std::endl;
    std::cout << "Знаки разные: " << (minVal < 0 && maxVal > 0 ? "да" : "нет") << std::endl;
    std::cout << "Разница модулей: " << abs(maxVal) - abs(minVal) << std::endl;

    // Условие: если знаки разные и модули отличаются не более чем на 2
    if (minVal < 0 && maxVal > 0 && (abs(maxVal) - abs(minVal) <= 2)) {
        std::cout << "Условие выполнено! Добавляем 0 в начало и в конец." << std::endl;
        vec.insert(vec.begin(), 0);
        vec.push_back(0);
    }
    else {
        std::cout << "Условие не выполнено! Добавляем 0 только в конец." << std::endl;
        vec.push_back(0);
    }

    std::cout << "После: ";
    showVector(vec);
}

// Функции для работы с array (Пункт 2)
void showArray(const std::array<int, 10>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) std::cout << " ";
    }
    std::cout << "]\n";
}

// Демонстрация передачи по ЗНАЧЕНИЮ
void sortByValue(std::array<int, 10> arr) {
    // Сортировка по возрастанию
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    std::cout << "По возрастанию: ";
    showArray(arr);

    // Сортировка по убыванию
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] < arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    std::cout << "По убыванию: ";
    showArray(arr);
}

// Демонстрация передачи по ССЫЛКЕ
void sortByReference(std::array<int, 10>& arr) {
    // Сортировка по возрастанию
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    std::cout << "По возрастанию: ";
    showArray(arr);

    // Сортировка по убыванию
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] < arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    std::cout << "По убыванию: ";
    showArray(arr);
}

// Демонстрация передачи по УКАЗАТЕЛЮ
void sortByPointer(std::array<int, 10>* arr) {
    // Сортировка по возрастанию
    for (size_t i = 0; i < arr->size(); ++i) {
        for (size_t j = 0; j < arr->size() - 1; ++j) {
            if ((*arr)[j] > (*arr)[j + 1]) {
                std::swap((*arr)[j], (*arr)[j + 1]);
            }
        }
    }
    std::cout << "По возрастанию: ";
    showArray(*arr);

    // Сортировка по убыванию
    for (size_t i = 0; i < arr->size(); ++i) {
        for (size_t j = 0; j < arr->size() - 1; ++j) {
            if ((*arr)[j] < (*arr)[j + 1]) {
                std::swap((*arr)[j], (*arr)[j + 1]);
            }
        }
    }
    std::cout << "По убыванию: ";
    showArray(*arr);
}int main() {
    setlocale(LC_ALL, "RU");
    // Инициализация генератора случайных чисел
    srand(time(0));

    // Пункт 1: используем vector
    std::vector<int> vec(3);
    vec[0] = 1;
    vec[1] = 32;
    vec[2] = 4;

    int choice;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "0. Выход\n";
        std::cout << "1. Просмотр массива\n";
        std::cout << "2. Добавить элемент в начало\n";
        std::cout << "3. Добавить элемент в конец\n";
        std::cout << "4. Очистка массива\n";
        std::cout << "5. Поиск элемента\n";
        std::cout << "6. Задание варианта 8\n";
        std::cout << "7. Перейти к пункту 2 (работа с array)\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            showVector(vec);
            break;

        case 2: {
            int val;
            std::cout << "Значение: ";
            std::cin >> val;
            vec.insert(vec.begin(), val);
            break;
        }

        case 3: {
            int val;
            std::cout << "Значение: ";
            std::cin >> val;
            vec.push_back(val);
            break;
        }

        case 4:
            vec.clear();
            std::cout << "Массив очищен\n";
            break;

        case 5: {
            int val;
            std::cout << "Искать: ";
            std::cin >> val;
            std::cout << "[";
            for (size_t i = 0; i < vec.size(); ++i) {
                if (vec[i] == val) std::cout << i << " ";
            }
            std::cout << "]\n";
            break;
        }

        case 6:
            variantTask(vec);
            break;

        case 7: {
            std::cout << "\nПункт 2: Работа с std::array\n";

            // Начальный массив заполнить рандомными значениями из отрезка [-10;10]
            std::array<int, 10> arr;

            std::cout << "Заполняем массив 10 случайными числами [-10,10]:\n";
            // Простое заполнение случайными значениями
            for (int i = 0; i < 10; ++i) {
                arr[i] = rand() % 21 - 10;
            }
            std::cout << "Исходный массив: ";
            showArray(arr);

            std::cout << "\n1. Передача по ЗНАЧЕНИЮ:\n";
            std::cout << "   До вызова: ";
            showArray(arr);
            sortByValue(arr);
            std::cout << "   После вызова: ";
            showArray(arr);

            std::cout << "\n2. Передача по ССЫЛКЕ:\n";
            std::cout << "   До вызова: ";showArray(arr);
            sortByReference(arr);
            std::cout << "   После вызова: ";
            showArray(arr);

            std::cout << "\n3. Передача по УКАЗАТЕЛЮ:\n";
            std::cout << "   До вызова: ";
            showArray(arr);
            sortByPointer(&arr);
            std::cout << "   После вызова: ";
            showArray(arr);
            break;
        }

        case 0:
            std::cout << "Завершение программы.\n";
            break;

        default:
            std::cout << "Ошибка: неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}
