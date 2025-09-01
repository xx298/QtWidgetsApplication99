#ifndef ORDER_H
#define ORDER_H

#include <QDateTime>
#include "user.h"
#include "train.h"
#include "seat.h"
#include "station.h"

class Order
{
public:
    Order();
    Order(int id, const User& user, const Train& train, const Seat& seat, const Station& startStation, const Station& endStation, const QDate& travelDate, const QDateTime& orderTime, const QString& status);

    int getId() const;
    User getUser() const;
    Train getTrain() const;
    Seat getSeat() const;
    Station getStartStation() const;
    Station getEndStation() const;
    QDate getTravelDate() const;
    QDateTime getOrderTime() const;
    QString getStatus() const;

    void setId(int id);
    void setUser(const User& user);
    void setTrain(const Train& train);
    void setSeat(const Seat& seat);
    void setStartStation(const Station& startStation);
    void setEndStation(const Station& endStation);
    void setTravelDate(const QDate& travelDate);
    void setOrderTime(const QDateTime& orderTime);
    void setStatus(const QString& status);

private:
    int id;
    User user;
    Train train;
    Seat seat;
    Station startStation;
    Station endStation;
    QDate travelDate;
    QDateTime orderTime;
    QString status;
};

#endif // ORDER_H