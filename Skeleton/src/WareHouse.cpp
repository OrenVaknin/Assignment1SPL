#include "WareHouse.h"


WareHouse::WareHouse(const string& configFilePath) : actionsLog(), volunteers(), pendingOrders(),
inProcessOrders(), completedOrders(), customers(), customerCounter(0), volunteerCounter(0), orderCounter(0)
{
	ifstream configFile(configFilePath);

	if (!configFile.is_open()) {
		cerr << "Error: Unable to open the configuration file." << endl;
		// Handle the error accordingly
		return;
	}

	string line;
	while (getline(configFile, line))
	{
		// Ignore lines starting with '#'
		if (line.empty() || line[0] == '#')
			continue;


		// Remove comments at the end of the line
		line = line.substr(0, line.find('#'));

		istringstream iss(line);
		string type;
		iss >> type;

		if (type == "customer")
		{
			// # Customers - customer <customer_name> <customer_type> <customer_distance> <max_orders>
			string name, customerType;
			int distance, maxOrders;
			iss >> name >> customerType >> distance >> maxOrders;
			// Create Customer object and add it to your Warehouse
			if (customerType == "civilian")
				customers.push_back(new CivilianCustomer(nextCustomerId(), name, distance, maxOrders));
			else
				customers.push_back(new SoldierCustomer(nextCustomerId(), name, distance, maxOrders));
		}

		else if (type == "volunteer")
		{

			//# Volunteers - volunteer <volunteer_name> <volunteer_role> <volunteer_coolDown>/<volunteer_maxDistance> <distance_per_step>(for drivers only) <volunteer_maxOrders>(optional)
			string name, role;
			int cooldown, maxDistance, distancePerStep, maxOrders;
			iss >> name >> role;


			if (role == "collector" || role == "limited_collector")
			{
				iss >> cooldown >> maxOrders;

				if (iss.fail()) // no maxOrders has been given
					volunteers.push_back(new CollectorVolunteer(nextVolunteerId(), name, cooldown));
				else
					volunteers.push_back(new LimitedCollectorVolunteer(nextVolunteerId(), name, cooldown, maxOrders));
			}

			else if (role == "driver" || role == "limited_driver")
			{
				iss >> maxDistance, distancePerStep, maxOrders;

				if (iss.fail()) // no maxOrders has been given
					volunteers.push_back(new DriverVolunteer(nextVolunteerId(), name, maxDistance, distancePerStep));
				else
					volunteers.push_back(new LimitedDriverVolunteer(nextVolunteerId(), name, maxDistance, distancePerStep, maxOrders));
			}
		}
		else
			continue; // ERROR
	}

	configFile.close();
}

WareHouse::WareHouse(const WareHouse& other)
{
	isOpen = other.isOpen;
	customerCounter = other.customerCounter;
	volunteerCounter = other.volunteerCounter;
	orderCounter = other.orderCounter;

	for (BaseAction* a : other.actionsLog)
		addAction(a->clone());

	for (Volunteer* v : other.volunteers)
		this->volunteers.push_back(v->clone());

	for (Order* o : other.pendingOrders)
		this->pendingOrders.push_back(o->clone());
	
	for (Order* o : other.inProcessOrders)
		this->inProcessOrders.push_back(o->clone());

	for (Order* o : other.completedOrders)
		this->completedOrders.push_back(o->clone());

	for (Customer* c : other.customers)
		this->addCustomer(c->clone());
}

WareHouse* WareHouse::clone()
{
	return new WareHouse(*this);
}

void WareHouse::start() {
	open();
	while (isOpen)
		handleInputAction();
	
}
const vector<BaseAction*>& WareHouse::getActions() const
{
	return actionsLog;
}

void WareHouse::addOrder(Order* order)
{
	pendingOrders.push_back(order);
}

void WareHouse::addAction(BaseAction* action)
{
	actionsLog.push_back(action);
}

Customer& WareHouse::getCustomer(int customerId) const
{
	for (Customer* c : customers)
		if (c->getId() == customerId)
			return *c;

	//error
	return SoldierCustomer::getInvalidCustomer();
}

Volunteer& WareHouse::getVolunteer(int volunteerId) const
{
	for (Volunteer* v : volunteers)
		if (v->getId() == volunteerId)
			return *v;

	//error
	return DriverVolunteer::getInvalidVolunteer();
}
Order& WareHouse::getOrder(int orderId) const {

	Order* order = nullptr;

	for (Order* o : pendingOrders)
		if (o->getId() == orderId)
		{
			order = o;
			break;
		}
	if (order == nullptr)
		for (Order* o : inProcessOrders)
			if (o->getId() == orderId)
			{
				order = o;
				break;
			}

	if (order == nullptr)
		for (Order* o : completedOrders)
			if (o->getId() == orderId)
			{
				order = o;
				break;
			}

	if (order != nullptr)
		return *order;

	else
		// error
		return Order::getInvalidOrder();;
}

void WareHouse::close() {
	isOpen = false;
	clearMemory();
	delete this;
}
void WareHouse::open() {
	isOpen = true;
	cout << "Warehouse is open!" << endl;
}

void WareHouse::preformStep()
{
	bool freeCollector = true, freeDriver = true;
	// part 1
	for (Order* o : pendingOrders)
		switch (o->getStatus())
		{
		case OrderStatus::PENDING:
			if (freeCollector)
			{
				Volunteer* v = findFreeVolunteer(*o);
				if (v != nullptr)
				{
					o->setCollectorId(v->getId());
					v->acceptOrder(*o);
					o->setStatus(OrderStatus::COLLECTING);
					switchOrdersVector(o, pendingOrders, inProcessOrders);
				}
				else
					freeCollector = false;
			}
			break;

		case OrderStatus::COLLECTING:
			if (freeDriver)
			{
				Volunteer* v = findFreeVolunteer(*o);
				if (v != nullptr)
				{
					o->setDriverId(v->getId());
					v->acceptOrder(*o);
					o->setStatus(OrderStatus::DELIVERING);
					switchOrdersVector(o, pendingOrders, inProcessOrders);
				}
				else
					freeDriver = false;
			}
			break;

		default:
			// COMPLETED or DELIVERING
			// ERROR
			// TODO
			break;
		}

	// parts 2 - 4
	for (Volunteer* v : volunteers)
	{
		v->step(); // 2
		if (v->getActiveOrderId() == NO_ORDER) // 3
		{
			Order o = getOrder(v->getCompletedOrderId());
			if (o.getStatus() == OrderStatus::COLLECTING)
				switchOrdersVector(&o, inProcessOrders, pendingOrders);
			else if (o.getStatus() == OrderStatus::DELIVERING)
			{
				switchOrdersVector(&o, inProcessOrders, completedOrders);
				o.setStatus(OrderStatus::COMPLETED);
			}
		}

		if (!v->hasOrdersLeft()) // 4
		{
			auto it = find(volunteers.begin(), volunteers.end(), v);
			volunteers.erase(it);
			delete v;
		}
	}
}

int WareHouse::nextCustomerId()
{
	return customerCounter++;
}

int WareHouse::nextVolunteerId()
{
	return volunteerCounter++;
}

int WareHouse::nextOrderId()
{
	return orderCounter++;
}

int WareHouse::getCustomerCounter()
{
	return customerCounter;
}

int WareHouse::getOrderCounter()
{
	return orderCounter;
}

int WareHouse::getVolunteerCounter()
{
	return volunteerCounter;
}

void WareHouse::addVolunteer(Volunteer* volunteer)
{
	volunteers.push_back(volunteer);
}

void WareHouse::addCustomer(Customer* customer)
{
	customers.push_back(customer);
}

//void WareHouse::addCustomer(const CustomerType type, const string& name, int distance, int maxOrders)
//{
//	if (type == CustomerType::Soldier)
//		customers.push_back(new SoldierCustomer(nextCustomerId(), name, distance, maxOrders));
//	customers.push_back(new CivilianCustomer(nextCustomerId(), name, distance, maxOrders));
//}

const vector<Order*>& WareHouse::myOrders(int customerId)
{
	vector<Order*> my_orders =  vector<Order*>();
	for(Order* o : pendingOrders)
		if (o->getCustomerId() == customerId)
			my_orders.push_back(o);

	for (Order* o : inProcessOrders)
		if (o->getCustomerId() == customerId)
			my_orders.push_back(o);

	for (Order* o : completedOrders)
		if (o->getCustomerId() == customerId)
			my_orders.push_back(o);

	return my_orders;
}

Volunteer* WareHouse::findFreeVolunteer(const Order& order)
{
	for (Volunteer* v : volunteers)
		if (v->canTakeOrder(order))
			return v;
	return nullptr;
}

void WareHouse::switchOrdersVector(Order* p, vector<Order*>& source, vector<Order*>& destination)
{
	auto it = find(source.begin(), source.end(), p);
	if (it != source.end())
	{
		source.erase(it);
		destination.push_back(p);
	}
}

void WareHouse::clearMemory()
{
	for (BaseAction* action : actionsLog) 
		delete action;

	for (Volunteer* volunteer : volunteers)
		delete volunteer;

	for (Order* order : pendingOrders)
		delete order;
	
	for (Order* order : inProcessOrders)
		delete order;

	for (Order* order : completedOrders)
		delete order;

	for (Customer* customer : customers)
		delete customer;
}

void WareHouse::handleInputAction()
{
	string line;
	getline(cin, line);
	
	string actionType;
	istringstream iss(line);
	iss >> actionType;

	BaseAction* action;
	int userInputI1, userInputI2;

	if (actionType == "simulateStep")
		if (iss >> userInputI1) // numOfSteps
			action = new SimulateStep(userInputI1);

	else if (actionType == "order")
		if (iss >> userInputI1) // customerId
			action = new AddOrder(userInputI1);

	else if (actionType == "customer") {
		string userInputS1, userInputS2;

		// customerName, customerType, distance, maxOrders
		if (iss >> userInputS1 >> userInputS2 >> userInputI1 >> userInputI2 && (userInputS2 == "civilian" || userInputS2 == "soldier") && userInputI1>=0, userInputI2>=0)
			action = new AddCustomer(userInputS1, userInputS2, userInputI1, userInputI2);
	}

	else if (actionType == "orderStatus")
		if (iss >> userInputI1) // orderId
			action = new PrintOrderStatus(userInputI1);

	else if (actionType == "customerStatus")
		if (iss >> userInputI1) // customerID
			action = new PrintCustomerStatus(userInputI1);

	else if (actionType == "volunteerStatus")
		if (iss >> userInputI1) // volunteerID
			action = new PrintVolunteerStatus(userInputI1);

	else if (actionType == "log") 
		action = new PrintActionsLog();

	else if (actionType == "close")
		action = new Close();

	else if (actionType == "backup")
		action = new BackupWareHouse();

	else if (actionType == "Restore")
		action = new RestoreWareHouse();

	addAction(action);
	action->act(*this);
}


