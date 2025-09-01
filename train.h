#pragma once
#ifndef TRAIN_H
#define TRAIN_H
#include <QString>
#include "station.h"

class Train
{
public:
    Train();
    Train(int id, const QString& trainCode, const QString& type, const Station& startStation, const Station& endStation);

    int getId() const;
    QString getTrainCode() const;
    QString getType() const;
    Station getStartStation() const;
    Station getEndStation() const;

    void setId(int id);
    void setTrainCode(const QString& trainCode);
    void setType(const QString& type);
    void setStartStation(const Station& startStation);
    void setEndStation(const Station& endStation);

private:
    int id;
    QString trainCode;
    QString type;
    Station startStation;
    Station endStation;
};

#endif // TRAIN_H
