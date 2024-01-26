#include "Volunteer.h"

CollectorVolunteer::CollectorVolunteer(int id, const string& name, int coolDown)
    : Volunteer(id, name), coolDown(coolDown){}


CollectorVolunteer* CollectorVolunteer::clone() const {
    // Implement the clone function
}

void CollectorVolunteer::step() {
    // Implement the step function
}

int CollectorVolunteer::getCoolDown() const {
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const {
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown() {
    // Implement the decreaseCoolDown function
}

bool CollectorVolunteer::hasOrdersLeft() const {
    // Implement the hasOrdersLeft function
}

bool CollectorVolunteer::canTakeOrder(const Order& order) const {
    // Implement the canTakeOrder function
}

void CollectorVolunteer::acceptOrder(const Order& order) {
    // Implement the acceptOrder function
}

string CollectorVolunteer::toString() const {
    // Implement the toString function
}