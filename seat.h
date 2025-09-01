#pragma once
#ifndef SEAT_H
#define SEAT_H

#include <QString>
#include "train.h"

class Seat
{
public:
    Seat();
    Seat(int id, const Train& train, const QString& seatNo, const QString& seatType);

    int getId() const;
    Train getTrain() const;
    QString getSeatNo() const;
    QString getSeatType() const;

    void setId(int id);
    void setTrain(const Train& train);
    void setSeatNo(const QString& seatNo);
    void setSeatType(const QString& seatType);

private:
    int id;
    Train train;
    QString seatNo;
    QString seatType;
};

#endif // SEAT_H

