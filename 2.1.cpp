#include <iostream>
#include <string>

class Potion {
private:
    std::string name;         // название
    std::string description;  // описание
    double price;             // цена
    std::string base;         // основа
    int volume;               // объем (мл)

public:
    // конструктор по умолчанию
    Potion() {
        name = "Зелье";
        description = "Обычное зелье";
        price = 10.0;
        base = "вода";
        volume = 100;
        std::cout << "Вызван конструктор по умолчанию" << std::endl;
    }

    // конструктор копирования
    Potion(const Potion& p) {
        name = p.name;
        description = p.description;
        price = p.price;
        base = p.base;
        volume = p.volume;
        std::cout << "Вызван конструктор копирования" << std::endl;
    }

    // конструктор полного заполнения
    Potion(std::string n, std::string d, double pr, std::string b, int v) {
        name = n;
        description = d;
        price = pr;
        base = b;
        volume = v;
        std::cout << "Вызван конструктор полного заполнения" << std::endl;
    }

    // деструктор
    ~Potion() {
        std::cout << "Зелье '" << name << "' удалено" << std::endl;
    }

    // геттеры на все поля
    std::string getName() { return name; }
    std::string getDescription() { return description; }
    double getPrice() { return price; }
    std::string getBase() { return base; }
    int getVolume() { return volume; }

    // сеттер на цену
    void setPrice(double newPrice) {
        price = newPrice;
    }

    // вывод всей информации
    void showInfo() {
        std::cout << "Название: " << name << std::endl;
        std::cout << "Описание: " << description << std::endl;
        std::cout << "Цена: " << price << std::endl;
        std::cout << "Основа: " << base << std::endl;
        std::cout << "Объем: " << volume << " мл" << std::endl;
    }

    // сменить основу
    void changeBase(std::string newBase) {
        base = newBase;
    }

    // стпить зелье (фиксированный объем  20 мл)
    void drink() {
        int fixedAmount = 20;
        if (volume >= fixedAmount) {
            volume -= fixedAmount;
            std::cout << "Отпито " << fixedAmount << " мл зелья" << std::endl;
        }
        else {
            std::cout << "Недостаточно зелья для порции" << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    //3 объекта для демонстрации всех конструкторов
    std::cout << "=== Создание объекта 1 (конструктор по умолчанию) ===" << std::endl;
    Potion p1;  //конструктор по умолчанию

    std::cout << "\n=== Создание объекта 2 (конструктор полного заполнения) ===" << std::endl;
    Potion p2("Зелье силы", "Дает силу", 50.0, "винo", 50);  //конструктор полного заполнения

    std::cout << "\n=== Создание объекта 3 (конструктор копирования) ===" << std::endl;
    Potion p3(p2);  //конструктор копирования - копия p2

    std::cout << "\n=== Информация о всех объектах ===" << std::endl;
    std::cout << "Объект 1 (по умолчанию):" << std::endl;
    p1.showInfo();
    std::cout << std::endl;

    std::cout << "Объект 2 (полный конструктор):" << std::endl;
    p2.showInfo();
    std::cout << std::endl;

    std::cout << "Объект 3 (копия p2):" << std::endl;
    p3.showInfo();
    std::cout << std::endl;

    std::cout << "=== Изменение данных в копии (p3) ===" << std::endl;
    p3.changeBase("эссенция");
    p3.setPrice(55.0);
    std::cout << "Объект 3 после изменений:" << std::endl;
    p3.showInfo();
    std::cout << std::endl;

    // Тест методjd
    std::cout << "=== Тестирование методов на объекте 2 ===" << std::endl;
    std::cout << "Отпиваем зелье (фиксированный объем):" << std::endl;
    p2.drink();  // отпить зелье (20 мл)
    std::cout << "Текущий объем p2: " << p2.getVolume() << " мл" << std::endl;

    std::cout << "\nМеняем основу p2:" << std::endl;
    p2.changeBase("эссенция");
    std::cout << "Новая основа p2: " << p2.getBase() << std::endl;

    std::cout << "\nИзменяем цену p2:" << std::endl;
    p2.setPrice(60.0);
    std::cout << "Новая цена p2: " << p2.getPrice() << std::endl;

    std::cout << "\n=== Информация о объекте 2 после изменений ===" << std::endl;
    p2.showInfo();

    return 0;
}
