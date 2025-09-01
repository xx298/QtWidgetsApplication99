#include "order.h"

Order::Order() : id(-1) {}

Order::Order(int id, const User& user, const Train& train, const Seat& seat, const Station& startStation, const Station& endStation, const QDate& travelDate, const QDateTime& orderTime, const QString& status)
    : id(id), user(user), train(train), seat(seat), startStation(startStation), endStation(endStation), travelDate(travelDate), orderTime(orderTime), status(status) {
}

int Order::getId() const
{
    return id;
}

User Order::getUser() const
{
    return user;
}

Train Order::getTrain() const
{
    return train;
}

Seat Order::getSeat() const
{
    return seat;
}

Station Order::getStartStation() const
{
    return startStation;
}

Station Order::getEndStation() const
{
    return endStation;
}

QDate Order::getTravelDate() const
{
    return travelDate;
}

QDateTime Order::getOrderTime() const
{
    return orderTime;
}

QString Order::getStatus() const
{
    return status;
}

void Order::setId(int id)
{
    this->id = id;
}

void Order::setUser(const User& user)
{
    this->user = user;
}

void Order::setTrain(const Train& train)
{
    this->train = train;
}

void Order::setSeat(const Seat& seat)
{
    this->seat = seat;
}

void Order::setStartStation(const Station& startStation)
{
    this->startStation = startStation;
}

void Order::setEndStation(const Station& endStation)
{
    this->endStation = endStation;
}

void Order::setTravelDate(const QDate& travelDate)
{
    this->travelDate = travelDate;
}

void Order::setOrderTime(const QDateTime& orderTime)
{
    this->orderTime = orderTime;
}

void Order::setStatus(const QString& status)
{
    this->status = status;
}