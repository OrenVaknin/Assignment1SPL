#include <string>
#include <vector>
using std::string;
using std::vector;

int Customer::getId() const {
    return ID;
};
string Customer::&getName() const{
    return &name;
};
int Customer::getCustomerDistance() const{
    return locationDistance;
};
int Customer::getMaxOrders() const {
    return maxOrders;
};
int Customer::getNumOrders() const{
    return totalOrders;
};
bool Customer::canMakeOrder() const{
    return (getMaxOrders > getNumOrders);
}:
vector<int> Customer::getOrders(){
    return //??
};
int Customer::addOrder(int orderID){
    if (canMakeOrder){
        totalOrders++;
        return orderID;
    };
    return -1
};
virtual Customer // save for laterino