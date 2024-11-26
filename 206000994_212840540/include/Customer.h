#pragma once
#include <string>
#include <vector>

using namespace std;


class Order;

class Customer {
public:
    Customer(int id, const string &name, int locationDistance, int maxOrders);
    virtual ~Customer() = default;
    const string &getName() const;
    int getId() const;
    int getCustomerDistance() const;
    int getMaxOrders() const; //Returns maxOrders
    int getNumOrders() const; //Returns num of orders the customer has made so far
    bool canMakeOrder() const; //Returns true if the customer didn't reach max orders
    const vector<int> &getOrders() const;
    int addOrder(int orderId); //return OrderId if order was added successfully, -1 otherwise
    virtual Customer* clone() const = 0; // Return a copy of the customer

private:
    const int id;
    const string name;
    const int locationDistance;
    const int maxOrders;
    vector<int> ordersId;
};


class SoldierCustomer : public Customer {
public:
    SoldierCustomer(int id, const string& name, int locationDistance, int maxOrders);
    SoldierCustomer* clone() const override;
    static Customer& getInvalidCustomer();
private:

};

class CivilianCustomer : public Customer {
public:
    CivilianCustomer(int id, const string& name, int locationDistance, int maxOrders);
    CivilianCustomer* clone() const override;

private:

};