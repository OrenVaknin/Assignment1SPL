#include "BaseAction.h"

extern WareHouse* backup;

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
	cout << errorMsg;
}

string BaseAction::getErrorMsg() const
{
	return errorMsg;
}

string BaseAction::toString() const
{
	if (status == ActionStatus::COMPLETED)
		return "Completed";
	return "Error: " + errorMsg;
}
//-----------------------------------------------------------------


SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}

void SimulateStep::act(WareHouse& wareHouse)
{
	for (int i = 0; i < numOfSteps; i++)
		wareHouse.preformStep();
}

string SimulateStep::toString() const
{
	// step 3
	return "Step " + to_string(numOfSteps) + " " + BaseAction::toString();
}

SimulateStep* SimulateStep::clone() const
{
	return new SimulateStep(*this);

}
//-----------------------------------------------------------------


AddOrder::AddOrder(int id) : customerId(id) {}

void AddOrder::act(WareHouse& wareHouse)
{
	if (customerId >= 0 && customerId < wareHouse.getCustomerCounter())
	{
		Customer& cus = wareHouse.getCustomer(customerId);

		if (cus.getId()!=-1 && cus.canMakeOrder())
		{
			int id = wareHouse.nextOrderId();
			int dis = cus.getCustomerDistance();
			cus.addOrder(id);
			wareHouse.addOrder(new Order(id, customerId, dis));
		}
		else
			error("Cannot place this order�");
	}
	else
		error("Customer doesn�t exist");
}

string AddOrder::toString() const
{
	// order 4
	return "Order " + to_string(customerId) + " " + BaseAction::toString();
}

AddOrder* AddOrder::clone() const
{
	return new AddOrder(*this);
}
//-----------------------------------------------------------------


AddCustomer::AddCustomer(const string& customerName, const string& customerType, int distance, int maxOrders) :
	customerName(customerName), customerType(SetType(customerType)), distance(distance), maxOrders(maxOrders) {}

CustomerType AddCustomer::SetType(const string& customerType)
{
	if (customerType == "soldier")
		return CustomerType::Soldier;
	return CustomerType::Civilian;
}

void AddCustomer::act(WareHouse& wareHouse)
{
	//wareHouse.addCustomer(customerType, customerName, distance, maxOrders);
	Customer* c;
	if (customerType == CustomerType::Soldier)
		c = new SoldierCustomer(wareHouse.nextCustomerId(), customerName, distance, maxOrders);
	c = new CivilianCustomer(wareHouse.nextCustomerId(), customerName, distance, maxOrders);
	wareHouse.addCustomer(c);
}


AddCustomer* AddCustomer::clone() const
{
	return new AddCustomer(*this);
}

string AddCustomer::toString() const
{
	//  customer <customer_name> <customer_type> <customer_distance> <max_orders>
	string s = "Customer " + customerName + " ";
	s += customerType == CustomerType::Soldier ? " Soldier " : " Civilian ";
	s += distance + " " + maxOrders;
	return s + BaseAction::toString();
}
//-----------------------------------------------------------------



PrintOrderStatus::PrintOrderStatus(int id) : orderId(id) {}

void PrintOrderStatus::act(WareHouse& wareHouse)
{
	if (wareHouse.getOrderCounter() < orderId || orderId < 0)
		error("Order doesn�t exist");
	cout << wareHouse.getOrder(orderId).toString() << endl;
}

PrintOrderStatus* PrintOrderStatus::clone() const
{
	return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const
{
	// orderStatus <order_id>
	return "OrderStatus " + orderId + BaseAction::toString();
}
//-----------------------------------------------------------------



PrintCustomerStatus::PrintCustomerStatus(int customerId) : customerId(customerId) {}

void PrintCustomerStatus::act(WareHouse& wareHouse)
{
	if (customerId<0 || customerId>wareHouse.getCustomerCounter())
		error("Customer doesn't exist");

	cout << "CustomerID: " + to_string(customerId) + "\n";

	for (Order* o : wareHouse.myOrders(customerId))
		cout << "\n" + o->toString();
	cout << "numOrdersLeft: " + to_string(wareHouse.getCustomer(customerId).getMaxOrders() - wareHouse.getCustomer(customerId).getNumOrders()) + "\n";
}

PrintCustomerStatus* PrintCustomerStatus::clone() const
{
	return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const
{
	// customerStatus <customer_id>
	return "CustomerStatus " + customerId + BaseAction::toString();
}

//-----------------------------------------------------------------



PrintVolunteerStatus::PrintVolunteerStatus(int id) : volunteerId(id) {}

void PrintVolunteerStatus::act(WareHouse& wareHouse)
{
	cout << wareHouse.getVolunteer(volunteerId).toString();
}

PrintVolunteerStatus* PrintVolunteerStatus::clone() const
{
	return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const
{
	//  volunteerStatus <volunteer_id>
	return "VolunteerStatus " + volunteerId + BaseAction::toString();
}
//-----------------------------------------------------------------



PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(WareHouse& wareHouse)
{
	for (BaseAction* a : wareHouse.getActions())
		cout << a->toString() + "\n";
}

PrintActionsLog* PrintActionsLog::clone() const
{
	return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const
{
	return "Log " + BaseAction::toString();
}
//-----------------------------------------------------------------



Close::Close() {}

void Close::act(WareHouse& wareHouse)
{
	for (int i = 0; i < wareHouse.getOrderCounter(); i++)
		cout << wareHouse.getOrder(i).toStringByStats();
	wareHouse.close();
}

Close* Close::clone() const
{
	return new Close(*this);
}

string Close::toString() const
{
	return "Close " + BaseAction::toString();
}
//-----------------------------------------------------------------



BackupWareHouse::BackupWareHouse() {}

void BackupWareHouse::act(WareHouse& wareHouse)
{
	if (backup != nullptr)
		backup->close();
	backup = wareHouse.clone();
}

BackupWareHouse* BackupWareHouse::clone() const
{
	return new BackupWareHouse(*this);
}

string BackupWareHouse::toString() const
{
	return "BackUp " + BaseAction::toString();
}
//-----------------------------------------------------------------



RestoreWareHouse::RestoreWareHouse() {}

void RestoreWareHouse::act(WareHouse& wareHouse)
{
	if (backup != nullptr) {
		backup->clone();
		//wareHouse.reconstruction();
	}
}

RestoreWareHouse* RestoreWareHouse::clone() const
{
	return new RestoreWareHouse(*this);
}

string RestoreWareHouse::toString() const
{
	if (backup == nullptr) {
		return "No backup available";
	}
	return "Restore " + BaseAction::toString();
}
