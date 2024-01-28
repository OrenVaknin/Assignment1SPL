#include "WareHouse.h"


WareHouse::WareHouse(const string& configFilePath) {
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
				customers.push_back(new CivilianCustomer(0, name, distance, maxOrders));
			else
				customers.push_back(new SoldierCustomer(0, name, distance, maxOrders));
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
					volunteers.push_back(new CollectorVolunteer(0, name, cooldown));
				else
					volunteers.push_back(new LimitedCollectorVolunteer(0, name, cooldown, maxOrders));
			}

			else if (role == "driver" || role == "limited_driver")
			{
				iss >> maxDistance, distancePerStep, maxOrders;

				if (iss.fail()) // no maxOrders has been given
					volunteers.push_back(new DriverVolunteer(0, name, maxDistance, distancePerStep));
				else
					volunteers.push_back(new LimitedDriverVolunteer(0, name, maxDistance, distancePerStep, maxOrders));
			}
		}
		else
			continue; // ERROR
	}

	configFile.close();
}

void WareHouse::start() {
	open();
}
const vector<BaseAction*>& WareHouse::getActions() const
{
	return actionsLog;
}

void WareHouse::addOrder(Order* order)
{
	//this->ID = order.getId;
	//pendingOrders.push_back(order);
}

void WareHouse::addAction(BaseAction* action)
{
	//actionsLog.push_back(action);
}

Customer& WareHouse::getCustomer(int customerId) const
{
	//x= look for the volunteer with the id in the array
	//return *Customers[x];
}

Volunteer& WareHouse::getVolunteer(int volunteerId) const
{
	//x= look for the volunteer with the id in the array
	//return *volunteers[x];
}
Order& WareHouse::getOrder(int orderId) const {
	//fill
}

void WareHouse::close() {
	isOpen = false;
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

	// part 2 - 4
	for (Volunteer* v : volunteers)
	{
		v->step(); // 2
		if (v->getActiveOrderId() == NO_ORDER)
		{
			Order o = getOrder(v->getCompletedOrderId());
			if (o.getStatus() == OrderStatus::COLLECTING)
				switchOrdersVector(&o, inProcessOrders, pendingOrders);
			else if (o.getStatus() == OrderStatus::DELIVERING)
			{
				switchOrdersVector(&o, inProcessOrders, completedOrders);
			}
				
		}

	}
}

Volunteer* WareHouse::findFreeVolunteer(const Order& order)
{
	for (Volunteer* v : volunteers)
		if (v->canTakeOrder(order))
			return v;
	return nullptr;
}

void WareHouse::switchOrdersVector(Order* p, std::vector<Order*>& source, std::vector<Order*>& destination)
{
	auto it = std::find(source.begin(), source.end(), p);
	if (it != source.end())
	{
		source.erase(it);
		destination.push_back(p);
	}
}

