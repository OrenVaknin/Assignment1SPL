#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include<algorithm>

#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
//#include "BaseAction.h"

class BaseAction;
//class Volunteer;


using namespace std;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.

class WareHouse {

public:
    
    WareHouse(const string &configFilePath);
    WareHouse(const WareHouse& other);
    WareHouse(WareHouse&& other);
    WareHouse& operator=(const WareHouse& other);
    ~WareHouse();
    WareHouse* clone();
    void start();
    void addOrder(Order* order);
    void addAction(BaseAction* action);
    Customer& getCustomer(int customerId) const;
    Volunteer& getVolunteer(int volunteerId) const;
    Order& getOrder(int orderId) const;
    const vector<BaseAction*>& getActions() const;
    void close();
    void open();
    void preformStep();
    int nextCustomerId();
    int nextVolunteerId();
    int nextOrderId();
    int getCustomerCounter();
    int getOrderCounter();
    int getVolunteerCounter();
    void addVolunteer(Volunteer* volunteer);
    void addCustomer(Customer* customer);
    //void addCustomer(const CustomerType type, const string& name, int distance, int maxOrders); 
    //const vector<Order*>& myOrders(int customerId);
    void myOrders(int customerId, vector<Order*>*);
    void test();
    
private:
    bool isOpen;
    vector<BaseAction*> actionsLog;
    vector<Volunteer*> volunteers;
    vector<Order*> pendingOrders;  
    vector<Order*> inProcessOrders;
    vector<Order*> completedOrders;
    vector<Customer*> customers;
    int customerCounter; //For assigning unique customer IDs
    int volunteerCounter; //For assigning unique volunteer IDs
    int orderCounter;
    Volunteer* findFreeVolunteer(const Order& order);
    void switchOrdersVector(int order_id, vector<Order*>& source, vector<Order*>& destination);
    void handleInputAction();
    void clearMemory();
};



