#include <iostream>
#include <string>
#include <locale>

using namespace std;

class Potion {
private:
    string name;
    string description;

protected:
    double price;
    string base;

public:
    double volume;

    Potion()
        : name("Неизвестно"),
        description("Нет описания"),
        price(0.0),
        base("Корень Мандрагоры"),
        volume(100.0) {}

    Potion(string n, string d, double p, string b, double v)
        : name(n),
        description(d),
        price(p),
        base(b),
        volume(v) {}

    Potion(const Potion& other)
        : name(other.name),
        description(other.description),
        price(other.price),
        base(other.base),
        volume(other.volume) {}

    ~Potion() {
        cout << "[Destructor] Potion: " << name << endl;
    }

    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    string getBase() const { return base; }
    double getVolume() const { return volume; }

    void setName(string n) {
        if (!n.empty()) name = n;
    }

    void setDescription(string d) {
        if (!d.empty()) description = d;
    }

    void setPrice(double p) {
        if (p >= 0) price = p;
    }

    void setBase(string b) {
        if (!b.empty()) base = b;
    }

    void printInfo() const {
        cout << "--- Potion Info ---" << endl;
        cout << "Name:        " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Price:       " << price << " алхимических жетонов" << endl;
        cout << "Base:        " << base << endl;
        cout << "Volume:      " << volume << " ml" << endl;
        cout << "-------------------" << endl;
    }

    void changeBase(string newBase) {
        if (!newBase.empty()) base = newBase;
    }

    void changeBase() {
        base = "Корень Мандрагоры";
    }

    void drink() {
        const double sip = 50.0;
        volume = (volume > sip) ? volume - sip : 0;
    }
};

int main() {
    setlocale(LC_ALL, "");

    Potion p1;
    p1.printInfo();
    cout << endl;

    Potion p2("Эликсир бодрости", "Восстанавливает энергию на 8 часов", 25.5, "Лепестки ромашки", 200.0);
    p2.printInfo();
    cout << endl;

    p2.setPrice(30.0);
    p2.changeBase("Корень мандрагоры");
    p2.changeBase();
    p2.drink();

    cout << "Объём после использования: " << p2.getVolume() << " мл" << endl;

    return 0;
}