#include "WareHous.h"
//to add a builder
void WareHouse::printActionsLogs(){
    print(AllActions);
    //<action_1_name> <action_1_args> <action_1_status>
}
void WareHouse::start() {
    // COMPLETE
}
const vector<BaseAction*>& WareHouse::getActionsLog() const {
    return actionsLog;
}
void WareHouse::addOrder(Order* order) {
    //this->ID = order.getId;
    //pendingOrders.push_back(order);
}
void WareHouse::addAction(BaseAction* action) {
    //actionsLog.push_back(action);
}
Customer& WareHouse::getCustomer(int customerId) const {
    //x= look for the volunteer with the id in the array
    return *Customers[x];
}
Volunteer& WareHouse::getVolunteer(int volunteerId) const {
    //x= look for the volunteer with the id in the array
    return *volunteers[x];
}
Order& WareHouse::getOrder(int orderId) const {
//fill
}
void WareHouse::close() {
    isOpen = false;
}
void WareHouse::open() {
    isOpen = true;
}

        WareHouse(const string &configFilePath);
        void start();
        const vector<BaseAction*> &getActionsLog() const;
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        void printActionsLogs();
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        void close();
        void open();