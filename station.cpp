#include "station.h"
Station::Station() : id(-1) {}

Station::Station(int id, const QString& name) : id(id), name(name) {}

int Station::getId() const
{
    return id;
}

QString Station::getName() const
{
    return name;
}

void Station::setId(int id)
{
    this->id = id;
}

void Station::setName(const QString& name)
{
    this->name = name;
}