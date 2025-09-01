#include "train_schedule.h"

TrainSchedule::TrainSchedule() : id(-1), stopOrder(-1) {}

TrainSchedule::TrainSchedule(int id, const Train& train, const Station& station, int stopOrder, const QDateTime& arriveTime, const QDateTime& departTime)
    : id(id), train(train), station(station), stopOrder(stopOrder), arriveTime(arriveTime), departTime(departTime) {
}

int TrainSchedule::getId() const
{
    return id;
}

Train TrainSchedule::getTrain() const
{
    return train;
}

Station TrainSchedule::getStation() const
{
    return station;
}

int TrainSchedule::getStopOrder() const
{
    return stopOrder;
}

QDateTime TrainSchedule::getArriveTime() const
{
    return arriveTime;
}

QDateTime TrainSchedule::getDepartTime() const
{
    return departTime;
}

void TrainSchedule::setId(int id)
{
    this->id = id;
}

void TrainSchedule::setTrain(const Train& train)
{
    this->train = train;
}

void TrainSchedule::setStation(const Station& station)
{
    this->station = station;
}

void TrainSchedule::setStopOrder(int stopOrder)
{
    this->stopOrder = stopOrder;
}

void TrainSchedule::setArriveTime(const QDateTime& arriveTime)
{
    this->arriveTime = arriveTime;
}

void TrainSchedule::setDepartTime(const QDateTime& departTime)
{
    this->departTime = departTime;
}