#include <iostream>
#include <string>

class Potion {
private:
    std::string name;
    std::string description;
    double price;
    std::string base;
    int volume;

public:
    // Конструктор по умолчанию
    Potion() {
        name = "Зелье";
        description = "Обычное зелье";
        price = 10.0;
        base = "вода";
        volume = 100;
    }

    // Конструктор копирования
    Potion(const Potion& p) {
        name = p.name;
        description = p.description;
        price = p.price;
        base = p.base;
        volume = p.volume;
    }

    // Конструктор полного заполнения
    Potion(std::string n, std::string d, double pr, std::string b, int v) {
        name = n;
        description = d;
        price = pr;
        base = b;
        volume = v;
    }

    // Деструктор
    ~Potion() {
        std::cout << "Зелье '" << name << "' удалено" << std::endl;
    }

    // Геттеры
    std::string getName() { return name; }
    std::string getDescription() { return description; }
    double getPrice() { return price; }
    std::string getBase() { return base; }
    int getVolume() { return volume; }

    // Сеттер цены
    void setPrice(double newPrice) {
        price = newPrice;
    }

    // Вывод информации
    void showInfo() {
        std::cout << "Название: " << name << std::endl;
        std::cout << "Описание: " << description << std::endl;
        std::cout << "Цена: " << price << std::endl;
        std::cout << "Основа: " << base << std::endl;
        std::cout << "Объем: " << volume << std::endl;
    }

    // Сменить основу
    void changeBase(std::string newBase) {
        base = newBase;
    }

    // Отпить зелье
    void drink(int amount) {
        if (volume >= amount) {
            volume -= amount;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    // Используем конструктор по умолчанию
    Potion p1;

    // Используем конструктор полного заполнения
    Potion p2("Зелье силы", "Дает силу", 50.0, "винo", 50);

    // Используем конструктор копирования
    Potion p3(p2);

    // Выводим информацию до использования
    p1.showInfo();
    std::cout << std::endl;
    p2.showInfo();
    std::cout << std::endl;
    p3.showInfo();
    std::cout << std::endl;

   // отпиваем зелье ---
    p2.drink(20);
    std::cout << "После того как отпили 20 мл из 'Зелья силы':" << std::endl;
    p2.showInfo();  // теперь объём = 30
    std::cout << std::endl;

    return 0;
}



//int main() {
    /*
    setlocale(LC_ALL, "ru");
    // Используем конструктор по умолчанию
    Potion p1;

    // Используем конструктор полного заполнения
    Potion p2("Зелье силы", "Дает силу", 50.0, "винo", 50);

    // Используем конструктор копирования
    Potion p3(p2);

    p1.showInfo();
    std::cout << std::endl;
    p2.showInfo();
    std::cout << std::endl;
    p3.showInfo();
    */
    //return 0;
//}