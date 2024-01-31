#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "BaseAction.h"

using namespace std;


// Warehouse responsible for Volunteers, Customers Actions, and Orders.



class WareHouse {

public:
    
    WareHouse(const string &configFilePath);
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
    void addCustomer(Customer* customer);
    const vector<Order*>& myOrders(int customerId);
    

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

    void switchOrdersVector(Order* p, std::vector<Order*>& source, std::vector<Order*>& destination);
    void clearMemory();
    string getInput();
};



