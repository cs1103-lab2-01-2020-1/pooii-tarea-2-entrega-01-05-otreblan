// Tarea 3
// Copyright © 2020 otreblan
//
// tarea-3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// tarea-3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with tarea-3.  If not, see <http://www.gnu.org/licenses/>.

#include <system.hpp>
#include <order.hpp>

#include <iostream>
#include <fstream>
#include <deque>

const time_t aru::System::bicycle_time = 20*60;
const time_t aru::System::truck_time = 5*60;

aru::System::System(ArgParser& args):
	args(args)
{
	char* XDG_CACHE_HOME = getenv("XDG_CACHE_HOME");
	if(XDG_CACHE_HOME == NULL)
	{
		cache_dir = getenv("HOME");
		cache_dir.append(".cache");
	}
	else
	{
		cache_dir = XDG_CACHE_HOME;
	}
	cache_dir.append("tarea-3");

	// mkdir -p
	fs::create_directories(cache_dir);

	bicycle = cache_dir;
	bicycle.append("bicycle.tsv");

	truck = cache_dir;
	truck.append("truck.tsv");
};

aru::System::~System(){};

bool aru::System::track(const std::string& user)
{
	std::deque<Order> truck_orders = parse_list(truck);
	std::deque<Order> bicycle_orders = parse_list(bicycle);

	recalculate_orders(truck_orders, Vehicle::truck);
	recalculate_orders(bicycle_orders, Vehicle::bicycle);

	if(!truck_orders.empty())
	{
		std::cout << "Camión\n";
		for(const auto& i: truck_orders)
		{
			if(i.user == user)
				i.fancy_print(std::cout);
		}
	}

	if(!bicycle_orders.empty())
	{
		std::cout << "Bicicleta\n";
		for(const auto& i: bicycle_orders)
		{
			if(i.user == user)
				i.fancy_print(std::cout);
		}
	}

	re_order(truck_orders, Vehicle::truck);
	re_order(bicycle_orders, Vehicle::bicycle);

	return true;
}

std::deque<aru::Order> aru::System::parse_list(fs::path vehicle)
{
	aru::Order order;
	std::deque<Order> resu;

	std::ifstream _vehicle(vehicle);
	if(_vehicle.is_open() && _vehicle.good())
	{
		while(_vehicle >> order)
		{
			resu.push_back(order);
		}
	}

	return resu;
}

bool aru::System::recalculate_orders(std::deque<Order>& orders, Vehicle vehicle)
{
	if(orders.empty())
		return false;

	time_t now = time(NULL);
	time_t vehicle_time;
	switch (vehicle)
	{
		case Vehicle::bicycle:
			vehicle_time = bicycle_time;
			break;
		case Vehicle::truck:
			vehicle_time = truck_time;
			break;
	}

	Order& first_order = *orders.begin();

	if(!first_order.exit_time.has_value())
		first_order.exit_time = first_order.time;

	while(true)
	{
		time_t exit_time = orders.begin()->exit_time.value();
		time_t arrival_time = exit_time + vehicle_time;

		if(arrival_time <= now)
		{
			orders.pop_front();

			if(orders.empty())
				break;

			Order& next_order = *orders.begin();

			if(next_order.time < arrival_time)
			{
				next_order.exit_time = arrival_time;
			}
			else
			{
				next_order.exit_time = next_order.time;
			}
		}
		else
			break;
	}

	return true;
}

bool aru::System::re_order(const std::deque<Order>& orders, Vehicle vehicle)
{
	if(orders.empty())
		return false;

	fs::path vehicle_path;
	switch (vehicle)
	{
		case Vehicle::bicycle:
			vehicle_path = bicycle;
			break;
		case Vehicle::truck:
			vehicle_path = truck;
			break;
	}
	std::ofstream order_list(vehicle_path);

	if(order_list.is_open() && order_list.good())
	{
		for(const auto& i: orders)
		{
			order_list << i;
		}
	}

	order_list.close();

	return true;
}

bool aru::System::order(const std::string& user,
	const std::string&                     destination,
	const Vehicle                          vehicle,
	const std::map<aru::Products, int>&   order)
{
	time_t now = time(NULL);

	std::ofstream _vehicle;

	aru::Order new_order = {now, std::nullopt, user, destination, vehicle, order};

	switch (vehicle)
	{
		case Vehicle::bicycle:
			_vehicle.open(bicycle, std::ios::app);
			break;
		case Vehicle::truck:
			_vehicle.open(truck, std::ios::app);
			break;
	}

	if(_vehicle.is_open() && _vehicle.good())
	{
		_vehicle << new_order;
	}

	_vehicle.close();

	return true;
}

bool aru::System::list()
{
	std::ifstream vehicle;

	vehicle.open(truck);
	list_print(vehicle, "Camión");
	vehicle.close();

	vehicle.open(bicycle);
	list_print(vehicle, "Bicicleta");
	vehicle.close();

	return true;
}

bool aru::System::list_print(std::ifstream& os, const std::string& vehicle)
{
	aru::Order order;
	if(os.is_open() && os.good())
	{
		std::cout << '\n' << vehicle << ":\n";
		while(os >> order)
		{
			order.fancy_print(std::cout);
		}
	}
	return true;
}

bool aru::System::start()
{
	if(args.action.has_value())
	{
		switch (*args.action)
		{
			case Action::help:
				args.usage();
				break;
			case Action::track:
				if(args.user.has_value())
				{
					track(args.user.value());
				}
				else
				{
					std::cerr << "Usuario no especificado\n";
					exit(EXIT_FAILURE);
				}
				break;
			case Action::list:
				list();
				break;
			case Action::order:
				if(!args.user.has_value())
				{
					std::cerr << "Usuario no especificado\n";
					exit(EXIT_FAILURE);
				}
				if(!args.destination.has_value())
				{
					std::cerr << "Destino no especificado\n";
					exit(EXIT_FAILURE);
				}
				if(!args.vehicle.has_value())
				{
					std::cerr << "Vehículo no especificado\n";
					exit(EXIT_FAILURE);
				}
				if(args.order.size() == 0)
				{
					std::cerr << "La orden no puede estar vacía\n";
					exit(EXIT_FAILURE);
				}
				order(args.user.value(),
					args.destination.value(),
					args.vehicle.value(),
					args.order);
				break;
		}
	}
	else
	{
		std::cerr << "Acción no especificada\n";
		exit(EXIT_FAILURE);
	}
	return true;
}
