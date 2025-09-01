#include "train.h"

Train::Train() : id(-1) {}

Train::Train(int id, const QString& trainCode, const QString& type, const Station& startStation, const Station& endStation)
    : id(id), trainCode(trainCode), type(type), startStation(startStation), endStation(endStation) {
}

int Train::getId() const
{
    return id;
}

QString Train::getTrainCode() const
{
    return trainCode;
}

QString Train::getType() const
{
    return type;
}

Station Train::getStartStation() const
{
    return startStation;
}

Station Train::getEndStation() const
{
    return endStation;
}

void Train::setId(int id)
{
    this->id = id;
}

void Train::setTrainCode(const QString& trainCode)
{
    this->trainCode = trainCode;
}

void Train::setType(const QString& type)
{
    this->type = type;
}

void Train::setStartStation(const Station& startStation)
{
    this->startStation = startStation;
}

void Train::setEndStation(const Station& endStation)
{
    this->endStation = endStation;
}