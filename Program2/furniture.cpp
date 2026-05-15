#include "furniture.h"

Furniture::Furniture()
    : name(""), description(""), legs(-1), handles(-1), drawers(-1), cost(-1)
{
}

Furniture::Furniture(QString name, QString description,
                     int legs, int handles, int drawers, float cost)
{
    this->name = name;
    this->description = description;
    this->legs = legs;
    this->handles = handles;
    this->drawers = drawers;
    this->cost = cost;
}

QString Furniture::getName() const { return name; }
QString Furniture::getDescription() const { return description; }
int Furniture::getLegs() const { return legs; }
int Furniture::getHandles() const { return handles; }
int Furniture::getDrawers() const { return drawers; }
float Furniture::getCost() const { return cost; }

void Furniture::setName(const QString& name) { this->name = name; }
void Furniture::setDescription(const QString& description) { this->description = description; }
void Furniture::setLegs(int legs) { this->legs = legs; }
void Furniture::setHandles(int handles) { this->handles = handles; }
void Furniture::setDrawers(int drawers) { this->drawers = drawers; }
void Furniture::setCost(float cost) { this->cost = cost; }

bool Furniture::isBroken() const
{
    if (name.isEmpty()) return true;
    if (legs < 0) return true;
    if (handles < 0) return true;
    if (drawers < 0) return true;
    if (cost < 0) return true;
    return false;
}

QJsonObject Furniture::toJson() const
{
    QJsonObject json;
    json["name"] = name;
    json["description"] = description;
    json["legs"] = legs;
    json["handles"] = handles;
    json["drawers"] = drawers;
    json["cost"] = cost;
    return json;
}

Furniture Furniture::fromJson(const QJsonObject& json)
{
    Furniture f;
    f.name = json["name"].toString("");
    f.description = json["description"].toString("");
    f.legs = json["legs"].toInt(-1);
    f.handles = json["handles"].toInt(-1);
    f.drawers = json["drawers"].toInt(-1);
    f.cost = json["cost"].toDouble(-1);
    return f;
}

bool Furniture::operator<(const Furniture& other) const
{
    return name > other.name;
}
