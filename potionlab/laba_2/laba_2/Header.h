#pragma once
#ifndef POTION_H
#define POTION_H

#include <iostream>
#include <string>
#include <vector>

class Potion {
private:
    std::string name;
    std::string description;
    std::vector<std::string>* ingredients; // динамическое поле

protected:
    double price;
    std::string base;

public:
    double volume;

    Potion();
    Potion(std::string n, std::string d, double p, std::string b, double v, std::vector<std::string> ing);
    Potion(const Potion& other);
    Potion& operator=(const Potion& other);
    ~Potion();

    // Геттеры
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    std::string getBase() const;
    double getVolume() const;
    std::vector<std::string> getIngredients() const;

    // Сеттеры
    void setName(std::string n);
    void setDescription(std::string d);
    void setPrice(double p);
    void setBase(std::string b);
    void setIngredients(std::vector<std::string> ing);

    void printInfo() const;
    void changeBase(std::string newBase);
    void changeBase();
    void drink();

    // Операторы по варианту 8
    Potion operator+(const Potion& other) const;
    Potion operator*(const Potion& other) const;
};

#endif