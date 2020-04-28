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
	return true;
}

bool aru::System::order(const std::string& user,
	const std::string&                     destination,
	const Vehicle                          vehicle,
	const std::map<aru::Products, int>&   order)
{
	time_t now;
	time(&now);

	std::ofstream vehiclePath;

	aru::Order new_order = {now, user, destination, vehicle, order};

	switch (vehicle)
	{
		case Vehicle::bicycle:
			vehiclePath.open(bicycle, std::ios::app);
			break;
		case Vehicle::truck:
			vehiclePath.open(truck, std::ios::app);
			break;
	}

	if(vehiclePath.is_open() && vehiclePath.good())
	{
		vehiclePath << new_order;
	}

	vehiclePath.close();

	return true;
}

bool aru::System::list()
{
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
