#ifndef FURNITURE_1_H
#define FURNITURE_1_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class Furniture
{
public:
    Furniture();
    Furniture(QString name, QString description,
              int legs, int handles, int drawers, float cost);

    // Геттеры
    QString getName() const;
    QString getDescription() const;
    int getLegs() const;
    int getHandles() const;
    int getDrawers() const;
    float getCost() const;

    // Сеттеры
    void setName(const QString& name);
    void setDescription(const QString& description);
    void setLegs(int legs);
    void setHandles(int handles);
    void setDrawers(int drawers);
    void setCost(float cost);

    // Проверка - битый объект или нет
    bool isBroken() const;

    // Преобразование в JSON
    QJsonObject toJson() const;

    // Преобразование из JSON
    static Furniture fromJson(const QJsonObject& json);

    // Для сортировки
    bool operator<(const Furniture& other) const;

private:
    QString name;
    QString description;
    int legs;
    int handles;
    int drawers;
    float cost;
};

#endif // FURNITURE_1_H
