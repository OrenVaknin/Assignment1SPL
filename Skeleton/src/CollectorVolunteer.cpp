#include "Volunteer.h"

CollectorVolunteer::CollectorVolunteer(int id, const string& name, int coolDown)
	: Volunteer(id, name), coolDown(coolDown) {}


CollectorVolunteer* CollectorVolunteer::clone() const {
	// Implement the clone function
}

void CollectorVolunteer::step() {
	decreaseCoolDown();
}

int CollectorVolunteer::getCoolDown() const {
	return coolDown;
}

int CollectorVolunteer::getTimeLeft() const {
	return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown() {

	timeLeft--;
	if (timeLeft == 0)
	{
		completedOrderId = activeOrderId;
		activeOrderId = NO_ORDER;
	}
}

bool CollectorVolunteer::hasOrdersLeft() const {
	return true;
}

bool CollectorVolunteer::canTakeOrder(const Order& order) const {
	return !isBusy() && order.getStatus() == OrderStatus::PENDING;
}

void CollectorVolunteer::acceptOrder(const Order& order) {
	timeLeft = coolDown;
	activeOrderId = order.getDriverId();
	activeOrderId = order.getId();
	
}

string CollectorVolunteer::toString() const {
	// Implement the toString function
}