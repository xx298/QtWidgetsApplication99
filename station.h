#pragma once
#ifndef STATION_H
#define STATION_H

#include <QString>

class Station
{
public:
    Station();
    Station(int id, const QString& name);

    int getId() const;
    QString getName() const;

    void setId(int id);
    void setName(const QString& name);

private:
    int id;
    QString name;
};

#endif // STATION_H
