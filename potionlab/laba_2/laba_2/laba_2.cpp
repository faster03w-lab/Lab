#include "Header.h"
#include <algorithm>
#include <random>

//конструктор по умолчанию
Potion::Potion()
    : name("Неизвестно"),
    description("Нет описания"),
    ingredients(new std::vector<std::string>()),
    price(0.0),
    base("Корень Мандрагоры"),
    volume(100.0) {
}

//конструктор с параметрами
Potion::Potion(std::string n, std::string d, double p, std::string b, double v, std::vector<std::string> ing)
    : name(n),
    description(d),
    ingredients(new std::vector<std::string>(ing)),
    price(p),
    base(b),
    volume(v) {
}

// конструктор копирования
Potion::Potion(const Potion& other)
    : name(other.name),
    description(other.description),
    ingredients(new std::vector<std::string>(*other.ingredients)),
    price(other.price),
    base(other.base),
    volume(other.volume) {
}

//оператор присваивания
Potion& Potion::operator=(const Potion& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        price = other.price;
        base = other.base;
        volume = other.volume;

        delete ingredients;
        ingredients = new std::vector<std::string>(*other.ingredients);
    }
    return *this;
}

//деструктор
Potion::~Potion() {
    std::cout << "[Destructor] Potion: " << name << ", очищаем вектор ингредиентов" << std::endl;
    ingredients->clear();
    delete ingredients;
}

//геттеры
std::string Potion::getName() const { return name; }
std::string Potion::getDescription() const { return description; }
double Potion::getPrice() const { return price; }
std::string Potion::getBase() const { return base; }
double Potion::getVolume() const { return volume; }
std::vector<std::string> Potion::getIngredients() const { return *ingredients; }

//сеттеры
void Potion::setName(std::string n) { if (!n.empty()) name = n; }
void Potion::setDescription(std::string d) { if (!d.empty()) description = d; }
void Potion::setPrice(double p) { if (p >= 0) price = p; }
void Potion::setBase(std::string b) { if (!b.empty()) base = b; }
void Potion::setIngredients(std::vector<std::string> ing) { *ingredients = ing; }

//печать информации
void Potion::printInfo() const {
    std::cout << "--- Potion Info ---" << std::endl;
    std::cout << "Имя:        " << name << std::endl;
    std::cout << "Описание: " << description << std::endl;
    std::cout << "Цена:       " << price << " алхимических жетонов" << std::endl;
    std::cout << "Основа:        " << base << std::endl;
    std::cout << "Объем      " << volume << " ml" << std::endl;
    std::cout << "Ингридиенты: ";
    for (const auto& ing : *ingredients)
        std::cout << ing << " ";
    std::cout << std::endl;
    std::cout << "-------------------" << std::endl;
}

//смена основы
void Potion::changeBase(std::string newBase) {
    if (!newBase.empty()) base = newBase;
}

void Potion::changeBase() {
    base = "Корень Мандрагоры";
}

//использование зелья
void Potion::drink() {
    const double sip = 50.0;
    volume = (volume > sip) ? volume - sip : 0;
}

//оператор +
Potion Potion::operator+(const Potion& other) const {
    std::string newName;
    if (name.find("(обн.)") == std::string::npos && other.name.find("(обн.)") == std::string::npos)
        newName = name + " + " + other.name;
    else
        newName = name + "(обн.)";

    std::string newBase = (volume >= other.volume) ? base : other.base;
    double newVolume = volume + other.volume;

    std::vector<std::string> newIngredients;
    for (const auto& ing : *ingredients)
        newIngredients.push_back(ing);

    for (const auto& ing : *other.ingredients) {
        if (std::find(newIngredients.begin(), newIngredients.end(), ing) != newIngredients.end())
            newIngredients.push_back(ing + " доп.");
        else
            newIngredients.push_back(ing);
    }

    return Potion(newName, "Смесь зелий", price + other.price, newBase, newVolume, newIngredients);
}

//оператор *
Potion Potion::operator*(const Potion& other) const {
    std::vector<std::string> bases = {
        "Корень Мандрагоры",
        "Лепестки ромашки",
        "Слеза единорога",
        "Пыльца феи"
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, bases.size() - 1);
    std::string newBase = bases[distr(gen)];

    double newVolume = (volume + other.volume) * 0.8;

    std::vector<std::string> newIngredients;
    for (const auto& ing : *ingredients) {
        if (std::find(other.ingredients->begin(), other.ingredients->end(), ing) != other.ingredients->end())
            newIngredients.push_back(ing);
    }
    newIngredients.push_back("хвост");
    newIngredients.push_back("вода");

    return Potion(name + " * " + other.name, "Мистическое зелье", price + other.price, newBase, newVolume, newIngredients);
}