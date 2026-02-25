#include <iostream>
#include <locale>
#include "Header.h"

int main() {
    setlocale(LC_ALL, "ru");

    Potion p1("Эликсир здоровья", "Восстанавливает HP", 15.0, "Корень Мандрагоры", 20.0,
        { "a", "b", "v", "g" });
    Potion p2("Зелье маны", "Восстанавливает MP", 10.0, "Лепестки ромашки", 10.0,
        { "v", "g", "m" });

    std::cout << "=== Исходные зелья ===" << std::endl;
    p1.printInfo();
    p2.printInfo();

    std::cout << "=== Оператор + ===" << std::endl;
    Potion p3 = p1 + p2;
    p3.printInfo();

    std::cout << "=== Оператор * ===" << std::endl;
    Potion p4 = p1 * p2;
    p4.printInfo();

    std::cout << "=== Проверка присваивания ===" << std::endl;
    Potion p5;
    p5 = p1;
    p5.printInfo();

    return 0;
}