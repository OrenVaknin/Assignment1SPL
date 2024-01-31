#include "Order.h"

Order::Order(int id, int customerId, int distance) :
	id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING),
	collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {}

int Order::getId() const {
	return id;
};
int Order::getCustomerId() const {
	return customerId;
};
void Order::setStatus(OrderStatus status) {
	this->status = status;
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
}
const string Order::toString() const
{
	std::string s = "OrderId: " + std::to_string(id) + "\n";
	s += "OrderStatus: ";
	switch (status) {
	case OrderStatus::PENDING:
		s += "Pending";
		break;
	case OrderStatus::COLLECTING:
		s += "Collecting";
		break;
	case OrderStatus::DELIVERING:
		s += "Delivering";
		break;
	case OrderStatus::COMPLETED:
		s += "Completed";
		break;
	}
	s += "\nCustomerId: " + std::to_string(customerId) + "\n";

	s += "Collector: " + (status == OrderStatus::PENDING) ? "None" : std::to_string(collectorId);

	s += "\nDriver: " + (status == OrderStatus::DELIVERING || status == OrderStatus::COMPLETED) ? std::to_string(driverId) : "None";

	return s;
}
int Order::getDistance() const
{
	return distance;
}

const string Order::toStringByStats() const
{
	string s = " ";
	switch (status) {
	case OrderStatus::PENDING:
		s += "Pending";
		break;
	case OrderStatus::COLLECTING:
		s += "Collecting";
		break;
	case OrderStatus::DELIVERING:
		s += "Delivering";
		break;
	case OrderStatus::COMPLETED:
		s += "Completed";
		break;
	}

	return id + " " + customerId + s;
}
