#pragma once

#include <string>
#include <vector>

using namespace std;


enum class OrderStatus {
    PENDING,
    COLLECTING,
    DELIVERING,
    COMPLETED,
};

#define NO_VOLUNTEER -1

class Order {

public:
    Order(int id, int customerId, int distance);
    Order* clone();        
    static Order& getInvalidOrder();
    int getId() const;
    int getCustomerId() const;
    void setStatus(OrderStatus status);
    void setCollectorId(int collectorId);
    void setDriverId(int driverId);
    int getCollectorId() const;
    int getDriverId() const;
    OrderStatus getStatus() const;
    const string toString() const;
    int getDistance() const;
    const string toStringByStats() const;
    const string toStringByStatsNID() const;
    
private:
    const int id;
    const int customerId;
    const int distance;
    OrderStatus status;
    int collectorId; //Initialized to NO_VOLUNTEER if no collector has been assigned yet
    int driverId; //Initialized to NO_VOLUNTEER if no driver has been assigned yet
};
