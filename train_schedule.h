#pragma once
#ifndef TRAIN_SCHEDULE_H
#define TRAIN_SCHEDULE_H

#include <QDateTime>
#include "train.h"
#include "station.h"

class TrainSchedule
{
public:
    TrainSchedule();
    TrainSchedule(int id, const Train& train, const Station& station, int stopOrder, const QDateTime& arriveTime, const QDateTime& departTime);

    int getId() const;
    Train getTrain() const;
    Station getStation() const;
    int getStopOrder() const;
    QDateTime getArriveTime() const;
    QDateTime getDepartTime() const;

    void setId(int id);
    void setTrain(const Train& train);
    void setStation(const Station& station);
    void setStopOrder(int stopOrder);
    void setArriveTime(const QDateTime& arriveTime);
    void setDepartTime(const QDateTime& departTime);

private:
    int id;
    Train train;
    Station station;
    int stopOrder;
    QDateTime arriveTime;
    QDateTime departTime;
};

#endif // TRAIN_SCHEDULE_H

