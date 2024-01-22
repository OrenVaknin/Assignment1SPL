#pragma once
#include <string>
#include <vector>
#include "Order.h"
using std::string;
using std::vector;

int Order::getId() const {
    return id;
};
int Order::getCustomerId() const {
    return customerId;
};
void Order::setStatus(OrderStatus status) {
    this->status = status; //should it be this way or the other??
};
void Order::setCollectorId(int collectorId) {
    this->collectorId = collectorId;
};
void Order::setDriverId(int driverId) {
    this->driverId = driverId;
};
int Order::getCollectorId() const {
    return collectorId;
};
int Order::getDriverId() const {
    return driverId;
};
OrderStatus Order::getStatus() const {
    return status;
};