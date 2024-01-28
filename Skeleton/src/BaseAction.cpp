#include "BaseAction.h"

BaseAction::BaseAction() {}

ActionStatus BaseAction::getStatus() const
{
	return ActionStatus();
}

void BaseAction::complete()
{
	status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg)
{
	status = ActionStatus::ERROR;
	this->errorMsg = errorMsg;
}

string BaseAction::getErrorMsg() const
{
	return errorMsg;
}
//-----------------------------------------------------------------


SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}

void SimulateStep::act(WareHouse& wareHouse)
{
	
}

std::string SimulateStep::toString() const
{
	return std::string();
}

SimulateStep* SimulateStep::clone() const
{
	return nullptr;
}
//-----------------------------------------------------------------


AddOrder::AddOrder(int id) : customerId(id) {}

void AddOrder::act(WareHouse& wareHouse)
{
}

string AddOrder::toString() const
{
	return string();
}

AddOrder* AddOrder::clone() const
{
	return nullptr;
}
//-----------------------------------------------------------------


AddCustomer::AddCustomer(const string& customerName, const string& customerType, int distance, int maxOrders) :
	customerName(customerName), customerType(SetType(customerType)), distance(distance), maxOrders(maxOrders)
{
}

CustomerType AddCustomer::SetType(const string& customerType)
{
	if (customerType == "soldier")
		return CustomerType::Soldier;
	return CustomerType::Civilian;
}

void AddCustomer::act(WareHouse& wareHouse)
{
}

AddCustomer* AddCustomer::clone() const
{
	return nullptr;
}

string AddCustomer::toString() const
{
	return string();
}
//-----------------------------------------------------------------



PrintOrderStatus::PrintOrderStatus(int id) : orderId(id) {}

void PrintOrderStatus::act(WareHouse& wareHouse)
{
}

PrintOrderStatus* PrintOrderStatus::clone() const
{
	return nullptr;
}

string PrintOrderStatus::toString() const
{
	return string();
}
//-----------------------------------------------------------------



PrintCustomerStatus::PrintCustomerStatus(int customerId) : customerId(customerId) {}

void PrintCustomerStatus::act(WareHouse& wareHouse)
{
}

PrintCustomerStatus* PrintCustomerStatus::clone() const
{
	return nullptr;
}

string PrintCustomerStatus::toString() const
{
	return string();
}

//-----------------------------------------------------------------



PrintVolunteerStatus::PrintVolunteerStatus(int id) : volunteerId(id) {}

void PrintVolunteerStatus::act(WareHouse& wareHouse)
{
}

PrintVolunteerStatus* PrintVolunteerStatus::clone() const
{
	return nullptr;
}

string PrintVolunteerStatus::toString() const
{
	return string();
}
//-----------------------------------------------------------------



PrintActionsLog::PrintActionsLog()
{
}

void PrintActionsLog::act(WareHouse& wareHouse)
{
}

PrintActionsLog* PrintActionsLog::clone() const
{
	return nullptr;
}

string PrintActionsLog::toString() const
{
	return string();
}
//-----------------------------------------------------------------



Close::Close() {}

void Close::act(WareHouse& wareHouse)
{
}

Close* Close::clone() const
{
	return nullptr;
}

string Close::toString() const
{
	return string();
}
//-----------------------------------------------------------------



BackupWareHouse::BackupWareHouse()
{
}

void BackupWareHouse::act(WareHouse& wareHouse)
{
}

BackupWareHouse* BackupWareHouse::clone() const
{
	return nullptr;
}

string BackupWareHouse::toString() const
{
	return string();
}
//-----------------------------------------------------------------



RestoreWareHouse::RestoreWareHouse()
{
}

void RestoreWareHouse::act(WareHouse& wareHouse)
{
}

RestoreWareHouse* RestoreWareHouse::clone() const
{
	return nullptr;
}

string RestoreWareHouse::toString() const
{
	return string();
}
