#include "Volunteer.h"

#define NO_ORDER -1

Volunteer::Volunteer(int id, const string& name): 
    id(id), name(name), completedOrderId(NO_ORDER), activeOrderId(NO_ORDER) {}

int Volunteer::getId() const {
    return id;
}

const string& Volunteer::getName() const
{
    return name;
}

int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
}

bool Volunteer::isBusy() const
{
    return activeOrderId != NO_ORDER;
}

string Volunteer::toString() const
{
	string s;
	s = "VolunteerID: " + to_string(getId()) + "\n";
	s += "Is Busy: " + isBusy() ? "True\n" : "False\n";
	s += "OrderID: " + (getActiveOrderId() != NO_ORDER ? to_string(getActiveOrderId()) : "None") + "\n";
	return s;
}