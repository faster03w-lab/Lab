#ifndef FURNITURE_H
#define FURNITURE_H

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

    QString getName() const;
    QString getDescription() const;
    int getLegs() const;
    int getHandles() const;
    int getDrawers() const;
    float getCost() const;

    void setName(const QString& name);
    void setDescription(const QString& description);
    void setLegs(int legs);
    void setHandles(int handles);
    void setDrawers(int drawers);
    void setCost(float cost);

    bool isBroken() const;
    QJsonObject toJson() const;
    static Furniture fromJson(const QJsonObject& json);
    bool operator<(const Furniture& other) const;

private:
    QString name;
    QString description;
    int legs;
    int handles;
    int drawers;
    float cost;
};

#endif // FURNITURE_H
