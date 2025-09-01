#include "seat.h"

Seat::Seat() : id(-1) {}

Seat::Seat(int id, const Train& train, const QString& seatNo, const QString& seatType)
    : id(id), train(train), seatNo(seatNo), seatType(seatType) {
}

int Seat::getId() const
{
    return id;
}

Train Seat::getTrain() const
{
    return train;
}

QString Seat::getSeatNo() const
{
    return seatNo;
}

QString Seat::getSeatType() const
{
    return seatType;
}

void Seat::setId(int id)
{
    this->id = id;
}

void Seat::setTrain(const Train& train)
{
    this->train = train;
}

void Seat::setSeatNo(const QString& seatNo)
{
    this->seatNo = seatNo;
}

void Seat::setSeatType(const QString& seatType)
{
    this->seatType = seatType;
}